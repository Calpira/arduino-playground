# Armado físico
 
Este proyecto está montado dentro de un caño de **PPN bicapa**, sin protoboard: todas las conexiones van soldadas directamente.
 
## Estructura del báculo (de arriba abajo)
 
1. **Punta — LED + resistencias**
2. **Arduino Nano + botón**: el botón queda a la altura de la mano.
3. **Pilas (6x AA)**: con tapa desmontable — es la única sección pensada para abrirse, así cambiar las pilas no implica desarmar el resto.
4. **Resto del caño**: el mango, fijo.


## Estructura del báculo (de arriba abajo)
 
1. **Punta — LED + resistencias**, en el extremo superior del caño.
2. **Mitad superior del caño**: hueca, solo pasan los cables que bajan desde el LED hasta el Arduino.
3. **Estructura central**: contiene el Arduino Nano, ubicada entre las dos mitades del caño. El botón sobresale, a la altura de la mano.
4. **Mitad inferior del caño**: contiene las pilas (6x AA), desmontable de la parte de arriba para poder acceder a las pilas en el recambio.
 
## Conexiones 
 
Es el mismo circuito descripto en el README:
- Cada unión (resistencia-LED, resistencia-cable, botón-cable) se suelda directamente y se cubre con cinta aisladora.

## Alimentación
 
- **6 pilas AA en serie (9V)** al pin **VIN** del Nano, GND de las pilas a **GND** del Nano.

### Portapilas casero
 
- Tubo hecho enrollando una lámina de plástico (de botella) alrededor de las 6 pilas ya puestas en fila, para que quede ajustado a su diámetro.
- Contactos metálicos (reciclados de un portapilas viejo) en cada extremo del tubo, haciendo presión contra el positivo y el negativo de la fila de pilas.




 
