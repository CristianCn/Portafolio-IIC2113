# Code Smells "Pistas para detectar mal código" - Portafolio Semana 5

En el siguiente portafolio se presentarán dos tipos de *code smells*, los que están directamente relacionados con el curso pues la semana pasada vimos específicamente algunos *code smells* y su relación con los principios *SOLID*, se hará un análisis de los siguientes:
*Long parameters list* y *Deodorant comment*.



## ¿Qué se entiende por Code smells?

[Martin Fowler](https://martinfowler.com/bliki/CodeSmell.html) en su libro "Refactoring", los define de la siguiente forma: "*A code smell is a surface indication that usually corresponds to a deeper problem in the system*", es decir, son pistas que nos llevan a pensar que el código presentado posee errores, las que se detectan por una simple inspección, pero podrían significar problemas más profundos. Para el presente porfafolio expondré como artefacto ejemplos de *code smells*, el primero fue sacado de [code smells (java edition)](https://elearning.industriallogic.com/gh/submit?Action=PageAction&album=recognizingSmells&path=recognizingSmells/longParameterList/longParameterList&devLanguage=Java) y el segundo corresponde a un código de elaboración propia.

## Long parameter list:

Este *Code Smell* se da cuando un método o una clase recibe una cantidad de parámetros muy grande. Como se puede ver a continuación en `userManager.create`, ya que la creación de un `userManager`  requiere 11 parámetros!

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

Un *code smell* de *long parameter list* puede ser originado de distintas formas, por ejemplo: al crear un método o clase donde muchos algoritmos son mezclados, al mezclar responsabilidades en una función, al añadir variables para controlar el flujo del método y otras más.

Aquí el método recibe demasiados parámetros, esto hace que sea difícil de utilizar y sea aún más difícil de entender. Por otro lado, este *code smell* nos podría entregar un indicio de que se está violando el primer principio *SOLID* de *single responsability*, si un parámetro cambia todos los usuarios del grupo deberían cambiar, por lo tanto la lógica de creación de usuarios probablemente no debería estar incluída en esta clase.

Sin embargo, me parece que se debe tener cuidado al realizar cambios basándose solamente en encontrar un *code smell* de *long parameter list*, estas "pistas" nos dan solo indicios y se debe ser muy cuidadoso si es que se realiza un cambio lógico o funcional del programa, esto requiere un mayor análisis de la lógica del código. Los *code smells* pueden ser encontrados simplemente a través de un impacto visual, pero al encontrarlos a simple vista solo podemos estar seguros de que el código podría requerir un *refactoring*.

Este *Code smell* se puede evitar separando responsabilidades y crear más métodos o clases, lo que sería solamente un refactoring, y no cambiaría la lógica de la clase o del método. Por ejemplo se podrían añadir objetos ya creados y así separar la responsabilidad de agregar un usuario y crear un usuario en dos clases distintas, además se podrían setear parámetros luego de la creación para evitar una lista tan larga.

## Deodorant Comment

Este *code smell* se da cuando los comentarios se utilizan para explicar el código de forma extensa, pues por si solo no se entiende. Cabe recordar que un buen código debería poder ser auto-documentado, es decir explicativo por si solo. 

Se puede ver un ejemplo en Python a continuación:


```python

def calc_something()
	
	a = 1.19 #Valor multiplicador del IVA
	b = 65700 
	#b Valor bruto sin impuesto del producto
		
	c = a*b
	
	print("El valor final es {}".format(c))
	#La función imprime el valor de un producto
	#incluyendo IVA y lo retorna
	
	return c
```

El ejemplo presentado es una exageración burda pero no está ajena a la realidad, existen muchos códigos que están comentados en forma extensa, ya que son muy difíciles de entender, debido a que los nombres de métodos y/o variables no son claros y las funciones tampoco presentan un hilo conductor organizado.

Este *code smell* se podría evitar haciendo un refactoring como el siguiente:

```python

def calcular_valor_neto()
	
	tasa_iva = 1.19
	monto_bruto = 65700 			
	monto_neto = monto_bruto * tasa_iva
	
	print("El valor final del producto es {}".format(monto_neto))	
	
	return monto_neto


```

Con este simple refactoring el código se torna autoexplicativo.

En mi opinión este *code smell* se debe tomar con cuidado, creo que el añadir algunos comentarios en el código a elementos claves no hacen que este se "ensucie", por el contrario, podrían serle de mucha utilidad a un desarrollador externo que esté tratando de entender un código que no es suyo.

Me parece que pequeños comentarios son útiles para otorgarle mayor claridad al código, por ejemplo el paradigma de programación funcional me parece sumamente elegante y preciso, pero si no se tiene conocimiento de él y el código no tiene ningún comentario resulta muy difícil de entender, en estos casos creo que los comentarios aportan. Por lo tanto, es importante poder evidenciar el momento donde este *code smell* es verdadero y los comentarios comienzan a "ensuciar" el código en vez de aportarle información útil.



## Conclusión:

Me parece que los *code smells* son excelentes indicadores de que algo podría estar mal en el código principal, pero se debe tener mucho criterio al ir más allá de realizar un *refactoring* y realizar un cambio de lógica en el programa, ya que puede ser que exista un indicio de mal código pero en realidad no lo sea, o que exista un *code smell* pero se justifique dentro del contexto del programa en particular. En estos casos no sería necesario modificar el programa que se está creando.
