# Code Smells "Long parameter list and " - Portafolio Semana 5

En el siguiente portafolio se presentarán dos tipos de *code smells*, los que están directamente relacionados con el curso pues la semana pasada vimos específicamente algunos *code smells* y su relación con los principios *SOLID*.

## ¿Qué se entiende por Code smells?

[Martin Fowler](https://martinfowler.com/bliki/CodeSmell.html) en su libro "Refactoring", los define de la siguiente forma: "*A code smell is a surface indication that usually corresponds to a deeper problem in the system*", es decir, son pistas que nos llevan a pensar que el código presentado posee errores, las que se detectan por una simple inspección pero podrían significar problemas más profundos. Para el presente porfafolio expondré como artefacto algunos ejemplos CodeSmells sacados de [code smells (java edition)](https://elearning.industriallogic.com/gh/submit?Action=PageAction&album=recognizingSmells&path=recognizingSmells/longParameterList/longParameterList&devLanguage=Java).

## Long parameter list:

Este *Code Smell* de da cuando un método o una clase recibe una cantidad de parámetros muy grande. Como se puede ver a continuación en `userManager.create` que recibe 11 parámetros!

```java
class OwnershipTest…
   private void createUserInGroup() {
      GroupManager groupManager = new GroupManager();
      Group group = groupManager.create(TEST_GROUP, 
      false, GroupProfile.UNLIMITED_LICENSES, "", 
      GroupProfile.ONE_YEAR, null);
      
      user = userManager.create(USER_NAME, group,
       USER_NAME, "joshua", USER_NAME, LANGUAGE, false,
       false, new Date(), "blah", new Date());
   }
```

Aquí el método recibe demasiados parámetros lo que directamente nos hace sospechar que se está violando el primer principio *SOLID* de single responsability, si un parámetro cambia, lo más probable es que todo el método cambie por lo que presenta más de una responsabilidad.

Este *Code smell* se puede evitar separando responsabilidades y crear más métodos o clases, lo que sería solamente un refactoring, sin cambiar la lógica d ela clase o método.

## Deodorant Comment

Este *code smell* se da cuando los comentarios se utilizan para explicar el código de forma extensa, pues por si solo no se entiende. Cabe recordar que un buen código debería poder ser auto-documentado, es decir explicativo por si solo. 

Se puede ver un ejemplo en Python a continuación:


```python

def calc_something()
	
	a = 1.19 #Valor multiplicador del IVA
	b = 65700 
	#b Valor bruto sin impuesto del producto
	#a comprar
	
	c = a*b
	
	print("El valor final es {}".format(c))
	#La función imprime el valor de un producto
	#incluyendo IVA y lo retorna
	
	return c
```

El ejemplo presentado es una exageración burda pero no está ajena a la realidad, a todos nos ha pasado encontrar un código comentado en forma extensa pues los nombres de las variables no son claros, los métodos no se entienden o no hay un hilo conductor claro en el programa.
## Conclusión:

Me parece que los *code smells* son un excelente indicador de que algo podría estar mal en el código principal, pero se debe tener mucho criterio al realizar refactoring, ya que puede ser que exista un indicio de mal código pero no lo sea, o que esté justificado por lo que no es necesario modificar el programa que se está creando.
