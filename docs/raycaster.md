# Raycaster no `cub3D` (inicialização, DDA e construção de colunas)

Este documento descreve o fluxo usado no projeto para renderizar cada frame 3D com raycasting, com foco em:

- Inicialização de câmera e raio por coluna
- Algoritmo DDA (`Digital Differential Analyzer`)
- Construção de cada coluna (altura, recorte e textura)

## 1) Fluxo geral de renderização

No loop de render (`src/render/render.c`), a função `cast_ray(game, data)` é chamada a cada frame (`src/render/raycaster_layer.c`):

1. `init_camera(&camera, game->map->player)`
2. Loop de `x = 0` até `width - 1`
3. `cast_single_column(game, data, &camera, x)`

Para cada coluna:

1. `get_camera_ray(camera, x, &game->ray)` monta direção do raio
2. `trace_ray(&game->ray, game->minimap, &game->ray.hit)` executa DDA e encontra parede
3. `perp = perp_dist_from_proj(...)` corrige distância perpendicular (evita fish-eye)
4. `render_wall_column(game, data, x, perp)` desenha a fatia vertical

---

## 2) Inicialização da câmera e do raio por coluna

### 2.1 Câmera (`init_camera`)

Em `src/engine/raycaster_init.c`:

- `camera.pos = player.pos`
- `camera.dir = (cos(angle), sin(angle))`
- `camera.plane = (-dir.y * 0.66, dir.x * 0.66)`
- `inv_screen_width = 1.0 / WINDOW_WIDTH`

O vetor `plane` representa o plano da câmera (largura do FOV).  
Com fator `0.66`, o FOV fica aproximadamente **66°**.

### 2.2 Raio da coluna `x` (`get_camera_ray`)

Em `src/engine/camera.c`:

```c
camera_x = 2.0f * x * inv_screen_width - 1.0f;
ray->fdir = camera.dir + camera.plane * camera_x;
```

- `camera_x = -1` na borda esquerda
- `camera_x = 0` no centro
- `camera_x ~ +1` na borda direita

#### Exemplo numérico

Assumindo:

- `WINDOW_WIDTH = 800`
- Jogador em `pos = (3.2, 2.4)`
- `angle = 0 rad` ⇒ `dir = (1, 0)`, `plane = (0, 0.66)`

Para `x = 0`:

- `camera_x = 2 * 0 / 800 - 1 = -1`
- `ray.fdir = (1, 0) + (0, 0.66)*(-1) = (1, -0.66)`

Para `x = 400` (centro):

- `camera_x = 0`
- `ray.fdir = (1, 0)`

---

## 3) DDA: como o raio atravessa o grid

O DDA é executado em `trace_ray` (`src/engine/first_ray.c`) com apoio de `src/engine/dda.c`.

## 3.1 Inicialização DDA (`init_dda_variables`)

- `rmap = floor(ray->fpos)` → célula atual no grid
- `rd = ray->fdir`
- `delta_dist.x = abs(1 / rd.x)` (ou `1e10` se `rd.x == 0`)
- `delta_dist.y = abs(1 / rd.y)` (ou `1e10` se `rd.y == 0`)

`delta_dist` indica quanto a distância acumulada aumenta ao cruzar uma linha vertical/horizontal da malha.

## 3.2 Distância inicial para a próxima linha de grade (`calc_side_dist`)

Com base no sinal de `rd`:

- define `step.x` e `step.y` como `+1` ou `-1`
- calcula `side_dist.x` e `side_dist.y` (distância até a primeira fronteira em X e Y)

## 3.3 Loop DDA (`update_ray_step`)

A cada iteração:

- se `side_dist.x < side_dist.y`: avança em X (`rmap.x += step.x`) e marca `side = 0`
- senão: avança em Y (`rmap.y += step.y`) e marca `side = 1`

Após andar uma célula, verifica se:

- saiu do mapa (`check_bounds`) ou
- atingiu parede (`grid[y][x] == '1'`)

## 3.4 Exemplo DDA passo a passo

Mesmo cenário:

- `fpos = (3.2, 2.4)`
- `fdir = (1, -0.66)` (coluna esquerda)

Inicialização:

- `rmap = (3, 2)`
- `delta_dist.x = abs(1/1) = 1.0`
- `delta_dist.y = abs(1/-0.66) ≈ 1.515`
- `step.x = +1`, `step.y = -1`
- `side_dist.x = (4.0 - 3.2) * 1.0 = 0.8`
- `side_dist.y = (2.4 - 2.0) * 1.515 ≈ 0.606`

Iterações:

1. `side_dist.y < side_dist.x` ⇒ anda em Y: `rmap = (3,1)`, `side=1`, `side_dist.y += 1.515` ⇒ `2.121`
2. agora `side_dist.x < side_dist.y` ⇒ anda em X: `rmap = (4,1)`, `side=0`
3. se `(4,1)` for parede, para

No hit, `update_ray_hit_data` calcula:

- `perp_dist` geométrica da interseção (pela fórmula de lado X/Y)
- `ray.hit` (ponto exato de impacto em coordenada contínua)
- `ray.hit_side` (`0` para cruzamento em linha vertical, `1` para horizontal)

---

## 4) Distância perpendicular e altura da coluna

Após o DDA, a coluna usa:

```c
perp = perp_dist_from_proj(&ray, camera_dir_unit(camera));
line_h = screen_h / perp;
```

`perp_dist_from_proj` faz o produto escalar entre o vetor hit e a direção unitária da câmera, removendo distorção fish-eye.

#### Exemplo

Se `perp = 3.8` e `screen_h = 600`:

- `line_h = 600 / 3.8 ≈ 157`
- `draw_start = -157/2 + 600/2 = 222`
- `draw_end = +157/2 + 600/2 = 378`

Ou seja, essa parede ocupa só a parte central da tela (mais distante).

---

## 5) Construção da coluna (textura + pixels)

Implementação principal: `render_wall_column` e `draw_column_pixels` em `src/engine/raycaster_column.c`.

## 5.1 Escolha da textura

`get_directional_texture(game)` escolhe textura por lado e direção do raio:

- `hit_side == 0` e `fdir.x > 0` ⇒ leste
- `hit_side == 0` e `fdir.x < 0` ⇒ oeste
- `hit_side == 1` e `fdir.y > 0` ⇒ sul
- `hit_side == 1` e `fdir.y < 0` ⇒ norte

## 5.2 Coordenada horizontal da textura (`tex_x`)

Primeiro pega a fração do ponto de hit:

- se `hit_side == 0`: usa `fmod(hit.y, 1.0)`
- se `hit_side == 1`: usa `fmod(hit.x, 1.0)`

Depois pode inverter:

```c
if ((hit_side == 0 && fdir.x < 0) || (hit_side == 1 && fdir.y > 0))
    wall_x_frac = 1.0 - wall_x_frac;
```

Por fim:

`tex_x = (int)(wall_x_frac * tex.width)`

#### Exemplo

- `hit_side = 0`
- `hit = (7.0, 2.4)` ⇒ `wall_x = fmod(2.4,1)=0.4`
- textura `64x64`
- `tex_x = (int)(0.4*64)=25`

## 5.3 Mapeamento vertical (`tex_y`) para cada pixel `y`

Para cada pixel da coluna visível:

```c
pos_in_wall = y - (screen_h - line_h)/2;
tex_y = pos_in_wall * tex.height / line_h;
```

Isso estica/comprime a textura para caber na altura projetada da parede.

#### Exemplo

Com `screen_h=600`, `line_h=157`, `tex.height=64`:

- para `y=300`:  
  `pos_in_wall = 300 - (600-157)/2 = 79`  
  `tex_y = 79*64/157 = 32` (aprox.)

## 5.4 Sombreamento final

`get_column_color` passa o texel para `sample_shade_pixel`, que aplica:

1. escurecimento por lado (`side == 1` usa fator 0.6)
2. atenuação por distância (`exp(-distance * shadow_k) * light_intensity`)

Resultado: profundidade visual melhor e separação entre faces.

---

## 6) Resumo operacional por coluna

Para cada `x` da tela:

1. converte `x` em raio no espaço da câmera (`camera_x`)
2. usa DDA para achar primeira parede no grid
3. calcula distância perpendicular
4. converte distância em `line_h`
5. escolhe textura da face atingida
6. calcula `tex_x` e `tex_y` por pixel
7. desenha a coluna com shading

Esse ciclo completo transforma o mapa 2D (`grid`) na projeção pseudo-3D da cena.
