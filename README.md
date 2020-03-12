# FdF
Мой проект FdF для Школа21 от Сбербанк

Задача проекта - написать программу, которая отрисовывает заданную карту высот, используя библиотеку minilibx. Для более побробной информации см. файл [10_fdf.en.pdf](sbj/10_fdf.en.pdf).

Что бы запустить программу, сперва выполните `make`.    
Испльзуйте команду ниже для запуска программы.    
```
./fdf FILENAME
```
`FILENAME` - это файл с картой. Для удобства я добавил некоторые карты в папку `maps`.

__Обратите внимание__ Для лучше производительности, закройте назначение клавиш после старта программы клавишей `H`.

Программа откроется в новом окне и отрисует эту карту. Вы можете менять угол обзора, расстояние между точками, нажимая клавиши клавиатуры:    
`W, A, S, D` - изменить угл обзора по осям x и y.    
`Q, E` - изменить угл обзора по осяи z.    
`↑ ↓ ← →` - переместить карту в соответстующем направлении.    
`+, -` - Изменить размер (отдалить/приблизить) карты    
`Numpad1/Numpad3` - Изменить расстояние по оси x.    
`Numpad4/Numpad6` - Изменить расстояние по оси y.    
`Numpad7/Numpad9` - Изменить расстояние по оси z.     
`Numpad0` - сброс расстояний к стандартным.    
`Backspace` - Выставить расстояние по размеру окна.    
`Enter` - Выставить положение карты по центру окна.    
`Tab` - Вернуть стандартный угл обзора.    
`H` - Показать/скрыть назначение кнопок.    
`Esc` - Закрыть окно.

![img1](images/42-fdf.png)
![img2](images/france-fdf.png)
![img3](images/some_map-fdf.png)

Этот проект я делал совместно со студентом Школы @ftothmur. Он делал проверку файла и сохранение данных. Моя часть работы была в написании алгоритма отображения карты и ослеживания нажатий клавиш.

Финальный балл: 125%

2019, Moscow, Russia
