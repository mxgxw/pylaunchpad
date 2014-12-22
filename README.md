PyLaunchpad
===========

A very simple launchpad for samples and loops written in Python and Pygame.

Minimum requirements
====================

Python 2.7.5 and PyGame

How change the samples?
=======================

Put your samples inside the "samples" directory, files must be in ogg format.

To assign to each launch button use the following format:
```
-----------------------------------------
| 1-1.ogg | 1-2.ogg | 1-3.ogg | 1-4.ogg |
-----------------------------------------
| 2-1.ogg | 2-2.ogg | 2-3.ogg | 2-4.ogg |

-----------------------------------------
| 3-1.ogg | 3-2.ogg | 3-3.ogg | 3-4.ogg |
-----------------------------------------
| 4-1.ogg | 4-2.ogg | 4-3.ogg | 4-4.ogg |
-----------------------------------------
```
For the loops just put the files inside the "loops" directory
```
-----------
|  1.ogg  |
-----------
|  2.ogg  |
-----------
|  3.ogg  |
-----------
|  4.ogg  |
-----------
```
To make the samples and loops I recommend to use Audacity <http://audacity.sourceforge.net>,
it's free software, easy to use and you can export directly to ogg format.

Keyboard mapping
================

The keyboard is mapped in the following way:
```
Samples         | Loops
------------------------
| 1 | 2 | 3 | 4 |  F1  |
------------------------
| q | w | e | r |  F2  |
------------------------
| a | s | d | f |  F3  |
------------------------
| q | w | e | r |  F4  |
------------------------
```
How to use?
===========

To start open the console and execute:
```
  $ python pad.py
```
The launchpad works by default in "trigger" mode. Once you press the button the sample
is going to be played once as long you keep pressed the button. There is no limit for
the lenght of the sample.

Loops work by default in toggle mode, press once to start playing the loop and press it
again to stop it.

You can have several loops and samples playing at the same time, but keyboard could have
a limit of how many keys can be pressed at the same time, so take that in consideratio.

More infoFoobar
=========

You can visit <http://blog.teubi.co/> for more information.

Licensing
=========
PyLaunchpad is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PyLaunchpad is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PyLaunchpad.  If not, see <http://www.gnu.org/licenses/>.