# Code Smells "Pistas para detectar mal código" - Portafolio Semana 2

En el siguiente portafolio se presentarán dos tipos de *code smells*, los que están directamente relacionados con el curso pues se vieron algunos de ellos como indicios de que hay problemas en el código, además, se analizará el llamado `Future Envy` que relaciona los principios de `cohesión` y `acomplamiento` que revisamos.

## ¿Qué se entiende por Code smells?

[Martin Fowler](https://martinfowler.com/bliki/CodeSmell.html) en su libro "Refactoring", los define de la siguiente forma: "*A code smell is a surface indication that usually corresponds to a deeper problem in the system*", es decir, son pistas que nos llevan a pensar que el código presentado posee errores, las que se detectan por una simple inspección pero podrían significar problemas más profundos. Para el presente porfafolio expondré como artefacto algunos CodeSmells sacados de [codinghorror.com](https://blog.codinghorror.com/code-smells/) que me parecen frecuentes y los ejemplificaré con código.

## Feature Envy:

Este *Code Smell* de da cuando un método o una clase accesa más a métodos de otra clase o función que a las propias. Por ejemplo se puede ver en el siguiente código java (sacado de [code smells (Java edition)](http://bit.ly/1LmVYvu):

```java
public class Phone {
   private final String unformattedNumber;
   public Phone(String unformattedNumber) {
      this.unformattedNumber = unformattedNumber;
   }
   public String getAreaCode() {
      return unformattedNumber.substring(0,3);
   }
   public String getPrefix() {
      return unformattedNumber.substring(3,6);
   }
   public String getNumber() {
      return unformattedNumber.substring(6,10);
   }
}
public class Customer…
   private Phone mobilePhone;
   public String getMobilePhoneNumber() {
      return "(" +
         mobilePhone.getAreaCode() + ") " +
         mobilePhone.getPrefix() + "-" +
         mobilePhone.getNumber();
   }
```

Aquí la clase `Customer` accesa a los métodos de la clase `Phone` variadas veces, siendo este su comportamiento principal, por lo tanto nos hace pensar que sería mejor tener un método `getMobilePhoneNumber` en la clase `Phone`, de lo contrario estamos violando dos principios fundamentales del diseño de software, tendríamos un alto acoplamiento y baja cohesión en la clase `Customer`. Podemos ver que la responsabilidad de obtener un número no tiene relación con la clase `Customer`.

A este *Code smell* se evitar fácilmente haciendo el siguiente refactoring:

```java
public class Phone {
   private final String unformattedNumber;
   public Phone(String unformattedNumber) {
      this.unformattedNumber = unformattedNumber;
   }
   private String getAreaCode() {
      return unformattedNumber.substring(0,3);
   }
   private String getPrefix() {
      return unformattedNumber.substring(3,6);
   }
   private String getNumber() {
      return unformattedNumber.substring(6,10);
   }
   public String toFormattedString() {
      return "(" + getAreaCode() + ") " + getPrefix() + "-" + getNumber();
   }  
}
public class Customer…
   private Phone mobilePhone;
   public String getMobilePhoneNumber() {
      return mobilePhone.toFormattedString();
   }
```

Sin embargo, se debe tomar en cuenta de que este es un ejemplo trivial, pero un refactoring de *Feature Envy* real podría ser muy complicado por la cantidad de dependencias que podría haber. En el ejemplo el *code smell* desaparece pues la responsabilidad de armar el número telefónico se le traspasa a la clase `Phone`, la que lógicamente tendría que haberlo echo desde un principio.

## Comments

Este *code smell* sugiere que el código no debe tener comentarios que expliquen su funcionamiento de forma exhaustiva, el programa debe poder ser comprendido por alguien que maneje el lenguaje, sin tener grandes dificultades. Para esto se debe presentar el código de forma clara, con nombres de métodos y variables adecuados.

Ejemplo del indicio en ruby (extraído de [code-smells examples](https://github.com/lee-dohm/code-smells):

```ruby
# Indicates whether color is a valid SVG color string.
#
# SVG color descriptions are one of the following:
#
# * RGB values
#     * #rgb
#     * #rrggbb
#     * rgb(255, 0, 0) - not currently supported
#     * rgb(100%, 0%, 0%) - not currently supported
# * SVG Color names
def valid_color?(color)
  return color =~ /^#[0-9A-Fa-f]{3}([0-9A-Fa-f]{3})?$/ if color[0] == '#'

  COLOR_NAMES.include?(color)
end
```

Me parece que este es un claro ejemplo en dónde el método y las variables no son claras, por lo que se sobrecarga con comentarios explicativos, hecho que hace que el código no sea claro.
En mi opinión este *code smell* no es tan claro como el anterior, en el sentido de la rigidez con que se debe tomar, creo que los comentarios ayudan a entender el código en variadas ocasiones por lo que el cliché "*Good code is self-documented*" no es válido siempre. Para evaluar la validez de los comentarios en un código se deben analizar otras interrogantes como por ejemplo:
* ### ¿Estoy creando una API que otros desarrolladores leerán?
* ### ¿Estoy creando código que solo ocuparé yo?
* ### ¿Todo el equipo maneja en lenguaje/framework que ocupo?
* ### etc.

## Conclusión:

Me parece que los *code smells* son un excelente indicador de que algo podría estar mal en el código principal, pero se debe tener mucho criterio al realizar refactoring ya que puede ser de que exista un indicio de mal código pero no lo sea, o que este está justificado por lo que no es necesario modificar el programa que se está creando.
