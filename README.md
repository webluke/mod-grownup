# Grow Up
## mod-grownup 

This module adds a visual sense of growth and progression to characters, making low-level adventurers look like small “young” versions of their races who literally grow up into heroes over the course of their journey. At even higher levels, veteran heroes can loom larger than their peers (but within a safe cap).

### Features:
First Login / Character Creation:

- New characters begin their adventure smaller than normal (configurable, default 50% size).

Starter Growth (Level 1 → StarterMaxLevel, default 15):

- As the character levels up, their size grows linearly from the configured minimum (e.g. 60%) up to 100% (normal size) by the chosen cap level.

Normal Zone (Between StarterMaxLevel and HighLevelStart):
  
- Once characters reach normal size, they remain steady at 100% scale until they reach the next milestone.

High-Level Growth (above HighLevelStart, default 65):

- Beyond this level, players begin to grow again at a small, configurable percentage increase per level (for example, +0.5% per level).

Maximum Cap:

- To prevent absurd scaling or model breaking, the growth is limited by a maximum scale value (configurable, default 120%).

Announcements:

- Optional system messages on login, module enabled confirmation, and per‑level “you grew” notices.


# ![screenshot](https://raw.githubusercontent.com/webluke/mod-grownup/refs/heads/main/grownup.png) 

### This module currently requires:
- AzerothCore


### How to install
1. Simply place the module under the `modules` folder of your AzerothCore source folder.
2. Re-run cmake and launch a clean build of AzerothCore
3. Copy mod_grownup.conf.dist to mod_grownup.conf
4. Log in game, level up and enjoy.


## Credits
* [WebLuke](  https://github.com/WebLuke ): (Author of the module)

* Looking at other modules, and a little help from GPT-5.

* AzerothCore: [repository](https://github.com/azerothcore) - [website](http://azerothcore.org/) - [discord chat community](https://discord.gg/PaqQRkd)