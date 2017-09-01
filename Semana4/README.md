# SOLID princicles: Single Responsability - Portafolio Semana 4

El artefacto presentado esta semana es un ejempo del primer principio SOLID: Single responsability. El artefacto está escrito en Python y muestra de forma ejemplificada lo que quiere decir el principio. El ejemplo se puede encontrar en el siguiente vínculo:  [principios SOLID en python](https://miguelgomez.io/python/principios-solid-python/), aquí se muestran ejemplos para todos los principios, pero solo tomaré el primer ejemplo del principio nombrado por lo que el link con el documento completo queda solamente de referencia. El artefacto está estrechamente relacionado con la materia de la semana pues vimos los principios SOLID, pero analizaré solamente uno con ejemplos creados en Python, con el que estamos más familiarizados.

## Single Responsibility: Responsabilidad única

Este principio nos dice que una clase solo debería tener una única responsabilidad, es decir la clase debería sufrir cambios obligados en el caso que cambie una única responsabilidad y no que muchas responsabilidades puedan obligar a generar cambios en la clase (pues no debería tener más que una).

Es importante recalcar que el principio no quiere decir que una clase deba tener solo un método, sino que los cambios que se puedan hacer a ésta deben estar regidos solo por una fuente de cambio.

## Análisis del artefacto

A continación se muestra una clase `Vehicle` escrita en Python.

```python
class Vehicle(object):
    def __init__(self, name):
        self._name = name
	self._persistence = MySQLdb.connect()
        self._engine = Engine()

    def getName():
        return self._name()

    def getEngineRPM():
        return self._engine.getRPM()

    def getMaxSpeed():
        return self._speed

    def print():
        return print ‘Vehicle: {}, Max Speed: {}, RMP: {}’.format(self._name, self._speed, self._engine.getRPM())

```

Podemos ver que en la clase se mezclan tres responsabilidades:

1. Tenemos la lógica de negocio: estamos manejando los datos y ofreciendo funcionalidades en la clase con los métodos `getEngineRPM()` y `getMaxSpeed()`.
2. Tenemos la lógica de persistencia: se está creando una conexión a una base de datos MySQL y se está guardando en una variable interna.
3. Tenemos la lógica de presentación: se manejan los prints al interior de la clase.

Tener tres lógicas no es beneficioso para el código, ya que tenemos tres fuentes distintas que podrían obligar a generar cambios en la clase. Por ejemplo: un cambio en el formato de impresión, un cambio en la base de datos o un cambio en la lógica del vehículo.

Esto va en contra de los principios fundamentales estudiados de tener una bajo acoplamiento y alta cohesión, lo que impide crear código mantenible a través del tiempo y también atenta contra la escalabilidad del código.

Estos problemas se podrían solucionar de la siguiente forma:

```python
class Vehicle(object):
    def __init__(self, name, engine):
        self._name = name
        self._engine = engine

    def getName(self):
        return self._name()

    def getEngineRPM(self):
        return self._engine.getRPM()

    def getMaxSpeed(self):
        return self._speed


class VehicleRepository(object):
    def __init__(self, vehicle, db)
        self._persistence = db
        self._vehicle = vehicle


class VehiclePrinter(object):
    def __init__(self, vehicle, db)
        self._persistence = db
        self._vehicle = vehicle
   
def print(self):
    return print ‘Vehicle: {}, Max Speed: {}, RMP:{}’.format(self._vehicle.getName(), self._vehicle.getMaxSpeed(), self._vehicle.getRPM())
```

Aquí separamos la lógica de persistencia y de presentación en dos clases, lo que reduce el acoplamiento y hace que las fuentes de cambio puedan afectar a clases distintas, por ende los cambios en la aplicación tienen menos repercusiones generales.

## Conclusión

Me parece que el artefacto es interesante porque ejemplifica de forma clara y concisa los principios SOLID, además utiliza un lenguaje que es más conocido para nosotros por nuestra formación (en relación al visto en clases). Me parece que aplicar los principios SOLID no resulta natural pues se prestan a malinterpretaciones, por ejemplo yo había entendido en primera instancia que era una mala práctica tener más métodos en una clase, pero el principio apunta a tener una sola fuente de responsabilidad y no a la cantidad de métodos que tenga una clase. Los principios SOLID ayudan a generar código con bajo acoplamiento y alta cohesión por lo que resulta fundamental tenerlos en cuenta a la hora de desarrollar para poder generar código mantenible y escalable.