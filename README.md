# NimbleGiantExam

## Explicacion del balanceador:

La idea es que al generarse un cubo, no pueda tener mas de 2 vecinos cuyo color sea el mismo que el que le toco de manera aleatoria.
Para esto busco un color al azar y veo cuantos vecinos de ese color hay, si hay 2 o menos, ese es su color, si no, paso al 
color siguiente, si me quedo sin colores, vuelvo al primero que le toco originalmente quedando este como el color del cubo.
Esto no significa que en el resultado final ninguno cubo tiene mas de 2 vvecinos del mismo color, ya que es al momento de 
crear el cubo actual y la piramide se forma de izquierda a derecha y de abajo para arriba.

El balanceador esta implementado en SelectColor_Implementation


## Otras consideraciones:

El proyecto fue hecho para correrse multiplayer Play As Client (es decir, con un servidor dedicado)

El codigo esta completamente en ingles (incluso algun que otro comentario, no del codigo, sino de por que esta ahi
como por ejemplo el balanceador.

Muchas gracias por su tiempo! 

Saludos!
