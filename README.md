![logo](logo.gif "VVVVVV")
-------
This is an altered version of the 2010 indie game VVVVVV using the officially released source code on [GitHub](https://github.com/TerryCavanagh/vvvvvv). This is used non-commercially for the experiment for my (Zeb De Roover) master thesis "Adaptive Checkpoints for Flow State Optimization in Video Games", as a student in the Master's program in Game Technology at the Breda University of applied sciences.

To enable the Dynamic Difficulty Adjustment, the variable "ddaEnabled" must be set to true in Game.cpp. If built normally, it will print the data file as a .txt file locally in the location of the game's save files. If built using Emscripten for a browser, it will try to export the data to a spreadsheet using a Google Apps Script. In order to build the game, the game's assets are necessary and need to be placed in MGT-DDA-VVVVVV\desktop_version\build\Debug. This is explained further in the [License](LICENSE.md).

The post-hoc validation of the DDA approach along with the data collected during the experiments, which has been anonymized, is all available in this repository in the folder "appendix" for analysis and review for any future research.

Licenses and many other files are left as-is, directly cloned from the official repository. The original VVVVVV is copyright of Terry Cavanagh © 2010-2020.

VVVVVV by [Terry Cavanagh](http://distractionware.com/), with music by [Magnus Pålsson](http://souleye.madtracker.net/).
The source code is available on [GitHub](https://github.com/TerryCavanagh/vvvvvv).
VVVVVV is still commercially available via [thelettervsixtim.es](https://thelettervsixtim.es/) if you'd like to support the game.

VVVVVV Credits
-------
- Created by [Terry Cavanagh](http://distractionware.com/)
- Room Names by [Bennett Foddy](http://www.foddy.net)
- Music by [Magnus Pålsson](https://magnuspalsson.com/)
- Metal Soundtrack by [FamilyJules](https://link.space/@familyjules)
- 2.0 Update (C++ Port) by [Simon Roth](http://www.machinestudios.co.uk)
- 2.2 Update (SDL2/PhysicsFS/Steamworks port) by [Ethan Lee](http://www.flibitijibibo.com/)
- Additional coding by [Misa Kai](https://infoteddy.info/)
- Beta Testing by Sam Kaplan and Pauli Kohberger
- Ending Picture by Pauli Kohberger
- Localisations by [their localisation teams](desktop_version/TRANSLATORS.txt)
- With additional contributions by [many others here on github](desktop_version/CONTRIBUTORS.txt)
