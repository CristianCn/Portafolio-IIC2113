# Resumen diseño detallado

## Diseño de software

Al crear software se pasa por tres etapas:

1. Modelación
2. Diseño
3. Construcción

Existen distintos diseños en software:

* Diseño de componentes: se describe cómo serán los componentes
* Diseño de interfaces: se describe como será la comunicación con sistemas externos (y humanos), externo puede ser del mismo sistema.
* Diseño de arquitectura: se describe la relación entre los componentes del sistema.
* Diseño de clases/datos: Esquema de clases y sus relaciones

## Principios fundamentales

* **Abstracción:** consiste en aislar un elemento de su contexto o del resto de los elementos que lo acompañan, se busca hacer énfasis en responder la pregunta ¿qué hace? más que el ¿cómo?, concepto de caja negra. La abstracción permite tener código más claro, entendible y mantenible. La abstracción es el proceso de acercarse a la generalización más que a la especialización.
* **Ocultamiento:** David Parnas que los módulos no deben comenzar listando las difíciles decisiones qué hace cada cosa y que son propensas a cambio, sino que exponer modulos que oculten el cómo se hace y expongan las decisiones tomadas que se pueden tomar solamente. Las decisiones tienden a trascender en el tiempo. Como ocultar en OOP: Interfaces, modificadores de acceso, headers, paquetes, dll, librearias, etc. Esto crea encapsulamiento de funcionalidades. El hacer cambios en un componente encapsulado entrega mantenibilidad, extensibilidad y reusabilidad es decir simpleza, las interfaces no cambian.
* **Acomplamiento:** Medida de cuán conectados están dos subsistemas o clases.
* **Cohesión:** Medida de cúan relacionados están los datos, responsabilidades y métodos de una clase.

Para lograr bajo acoplamiento y alta cohesión hay que revisar diversas aristas:

**Acoplamiento:** De contenido, de control y de uso de tipos.
**Cohesión:** De capas, de comunicación, funcionalidades. 

### Bajo acoplamiento y alta cohesión es lo deseado!

Los proyectos de ingeniería de software generan mucha información. La información generada es importante para varias personas al interior del equipo de la empresa y también para el exterior, por lo que existen personas con tipos de conocimiento muy variado.

Se pueden dividir las preocupaciones de los participantes en distintos niveles:

### Modelo 4+1

  | Conceptual                       | Físico
-----------| ------------------------------------- | ----------------
Funcional      | Vista lógica   | Vista de implementación
No funcional       | Vista de procesos    | Vista física

Y al centro se agrega la vista de casos de uso.

* **vista lógica (conceptual y funcional):** Descomposición orientada a objetos, usada para el análisis funcional. La vista lógica está enfocada en describir la estructura y funcionalidad del sistema. Diagrama de clases y secuencia le interesa a desarrolladores.
* **vista de procesos (conceptual y no funcional):** Descomposición de procesos. Abstracciones principales de la vista lógica. Diagrama de actividad.Trata los aspectos dinámicos del sistema, explica los procesos de sistema y cómo se comunican. se enfoca en el comportamiento del sistema en tiempo de ejecución. La vista considera aspectos de concurrencia, distribución, rendimiento, escalabilidad. Le interesa a integradores de sistemas T.I. por ej 
* **vista de implementación (físico y funcional):** Descomposición de subsistemas. Arquitectura de componentes. Útil para el programador y gestor de software, se usan diagramas de componentes y paquetes
* **vista física (físico y no funcional):** Correspondencia software - hardware. Topología de hardware. Le interesa al ingeniero que hace el deploy, se utiliza diagrama de deploy.
* **vista holística o de casos de uso:** Comportamiento del sistema desde el punto de vista del usuario y otros interesados. Diagrama casos de uso. Usuario final o product owner

## Principios solid

S| Acrónimo                       | Concepto
-----------| ------------------------------------- | ----------------
S      |SRP   | Principio de responsabilidad única (Single responsibility principle) la noción de que un objeto solo debería tener una única responsabilidad.
O      | OCP    | Principio de abierto/cerrado (Open/closed principle) la noción de que las “entidades de software … deben estar abiertas para su extensión, pero cerradas para su modificación”.
L      | LSP    | Principio de sustitución de Liskov (Liskov substitution principle) la noción de que los “objetos de un programa deberían ser reemplazables por instancias de sus subtipos sin alterar el correcto funcionamiento del programa”. 
I  | 	ISP	  |  Principio de segregación de la interfaz (Interface segregation principle) la noción de que “muchas interfaces cliente específicas son mejores que una interfaz de propósito general”.5​
D  | 	DIP	  |  Principio de inversión de la dependencia (Dependency inversion principle)la noción de que se debe “depender de abstracciones, no depender de implementaciones”.5​ La Inyección de Dependencias es uno de los métodos que siguen este principio.

## Refactoring

Consiste en reformular el código para hacerlo más mantenible, los cambios están orientados a reformular el código en relación a su calidad pero NO a cambiar la lógica ni funcionamiento de este, es decir cambia la forma en qué está escrito pero no su comportamiento.

## CodeSmells 

**Bloaters:**

Bloaters son códigos,métodos y clases que tienen un tamaño muy grande, por ende es difícil trabajar con ellos. Usualmente estos codesmells no se identifican de buenas a primeras al crear código sino que aparecen a medida que los proyectos crecen y se vuelven más complicados.

Dentro de estos tenemos los siguientes smells:

* Métodos muy largos
* Clases muy largas
* Lista de parámetros muy extensa
* Muchas clases repiten código, esto se da por el *copy-paste programming*
* Obsesión con datos primitivos: muchas veces resulta más eficiente crear una clase con un tipo de dato custom en vez de a la fuerza utilizar muchos integers por ej para representar una fecha.

**Object orientation abusers:**

Se refieren a smells que denotan un incorrecto uso de OOP, abusando de los principios que este paradigma entrega.

* Temporary field: fields que tienen valores pero solo se requieren para determinados casos, por ej. definir un valor "hardcodeado" para salvar un caso borde.
* Switch statements: usar muchos switch case o muchos ifs
* Refused bequest: Cuando se subclasea pero la subclase solo utiliza algunos métodos, los otros sobran y queda más lógica de la que debería o se implementan excepciones para manejar los métodos que no corresponden. Esto es herencia mal ocupada.
* Alternative classes with different interfaces: clases que hacen las mismas funciones pero tiene métodos que se llaman distinto.

**Change preventers:**

Smells relacionados a los cambios a efectuar en el código si una parte pequeña cambia, no deberían haber muchas dependencias si no son necesarias.

* Divergent change: Cuando todos los cambios que se hacen al programa se realizan sobre solo una clase, quizás la clase posee demasiada lógica y no posee poca cohesión.
* Shotgun surgery: Al revés del anterior un cambio pequeño hace que muchas clases deban cambiar.
* Paraller inheritance: cuando se crea una subclase para una clase y uno se encuentra en la obligación de crear una subclase para otra clase. Se podría estar duplicando código al crear dos subclases pero a veces tratan lógica distinta por lo que se permite.

**Dispensables:**

Cosas innecesarias

* Código duplicado
* Comentarios que expliquen el código (deberían ser muy cortos si es que hay)
* Código que no se usa o nunca se llega a él
* Lazy class: clase realizada pero que no tiene importancia podría ser perfectamente una función o algo más simple.
* Data class: clases que solo tienen atributos y los métodos son geters o seters pero no se tiene lógica, hay que ver bien si estas clases son necesarias.
* Speculative generality: clases creadas pero que no se ocupan, realizadas para mantenerse dry pero en verdad es una generalización que no se ocupa y queda solo la definición de la clase.

**Couplers:**

Contribución excesiva entre distintas clases, quizás existe una delegación excesiva.

* Message chains: Cuando se ven una serie de llamadas sucesivas, un ej callback hell de JS, `a=>b=>c=>d...`
* Innapropriate intimacy: una clase utiliza los atributos internos y métodos de otra clase.
* Middle Man: Una clase que no tenga lógica propia y sirva solo para delegar acciones desde una clase a otra. Para qué existe esta clase?
* Incomplete library class: librería incompleta, pasa a menudo que librerías no tienen todo lo que deberían y quedan obsoletas pues no se tiene acceso a cambiarlas.
* Feature envy: un método accesa más a información de otra clase más que a la propia información.

