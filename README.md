# SAL/T (Sistema de Aislamiento Limitado/Total)
## Introducción

Las formaciones ferroviarias cuentan con diferentes sistemas de seguridad a bordo. Los mismos son equipos que se encargan de supervisar el correcto funcionamiento de los subsistemas críticos. Ejemplos de los mismos son la seguridad de puertas, el sistema de hombre vivo y la protección de coche a la deriva.

Ante una falla en uno de estos subsistemas, una formación ferroviaria se detiene inmediatamente por la activación automática de las señales de corte de tracción (CT) y frenado de emergencia (FE). En esta situación el conductor debe llevar a la formación a un lugar seguro para que los pasajeros puedan descender y posteriormente a un taller para que pueda ser reparada.

El SAL/T es un sistema que le permitirá al conductor la activación y desactivación del modo aislado limitado. En este modo el equipo permite la circulación de la formación al desactivar las señales de corte de tracción y freno de emergencia generadas por los otros subsistemas. Para que esta operación se realice de forma segura se debe monitorear la velocidad de la formación de modo de evitar que supere cierto valor máximo.

Se considera un sistema crítico debido a que, en caso de fallar, puede ocasionar daños afectando negativamente la salud de las personas, al medio ambiente y/o generar grandes pérdidas materiales.

## Configuración

En la carpeta `model` se encuentran los diagramas de estado desarrollados con [YAKINDU Statechart Tools](https://www.itemis.com/en/yakindu/state-machine/) Professional Edition (version 3.5.12).

Para importar se deben seguir los siguientes pasos:

- Clonar este repositorio con el comando:
```
$ git clone https://github.com/nahueespinosa/salt
```
- Seleccionar el menú `File -> Import -> Existing Projects into Workspace` y buscar la carpeta del proyecto.