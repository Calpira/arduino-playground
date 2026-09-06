# Juego de luces RGB multimodo
 
Sistema de control para un LED RGB con varios modos de luz, manejados con un solo botón. Pensado originalmente para un báculo, pero sirve para cualquier armado que use un LED RGB.
 
## Componentes
 
- Arduino Nano
- LED RGB de cátodo común
- 3 resistencias de 220Ω (una por color: R, G, B)
- Pulsador (botón)
- Alimentación: 6 pilas AA (9V) al pin VIN
## Conexiones
 
| Componente | Pin Arduino Nano |
|---|---|
| LED - Rojo (con resistencia) | 9 |
| LED - Verde (con resistencia) | 10 |
| LED - Azul (con resistencia) | 11 |
| LED - Común (patita larga, sin resistencia) | GND |
| Botón - una pata | 2 |
| Botón - pata opuesta | GND |
| Pilas (+) | VIN |
| Pilas (-) | GND |
 
 
## Modos y controles
 
| Acción con el botón | Resultado |
|---|---|
| Click simple | Alterna entre modo **"calmado"** y modo **"fuego"** |
| Mantener apretado (~0.5s) | Activa **"carga de poder"** + **"modo fiesta"** |
| Doble click | Apaga / prende el LED |
 
Durante la carga de poder o el modo fiesta, cualquier apretón del botón interrumpe y vuelve al modo calmado.
 
### Descripción de los modos
 
- **Calmado**: efecto respiración en tono azul.
- **Fuego**: simulacion de llama en rojo/naranja, con chispas y caídas de brillo aleatorias.
- **Carga de poder**: flash que crece en intensidad y velocidad, de blanco a violeta, antepone al "modo fiesta".
- **Fiesta**: Colores que cambian aleatoriamente.
