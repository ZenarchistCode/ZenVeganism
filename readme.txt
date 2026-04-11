[h1]What Is This?[/h1]

This is the mod no one asked for.

Ever wondered what it would be like to survive the zombie apocalypse as a vegan?

Wonder no longer.

This mod adds a random chance for players to spawn restricted to a vegan diet.

Admins can configure the chance of spawning as a vegan and the list of prohibited foods in the JSON config (see Instructions section).

Once a player spawns as a vegan, they cannot eat any meat items (including fish), and they can't even eat honey - after all, they're vegan, and extremely dedicated to their diet.

Attempting to eat any item containing meat will result in the character throwing up their food, and the only cure is a respawn and hope you don't come back as a vegan a second time.

The one silver lining is that vegans recover their stamina 50% faster than anyone else, due to their increased health and fitness (configurable in the JSON file).

If you want a unique survival challenge and a good reason to grow your own vegetables... give it a try. 

Good luck. 

[h1]Installation Instructions:[/h1]

Note: ZenModCore is a dependency - https://steamcommunity.com/sharedfiles/filedetails/?id=3702420204

Install this mod like any other mod - copy it into your server folder and add it to your mods list. Make sure to copy the .bikey into your server keys if you're not using a server management tool like OmegaManager which does that automatically.

This mod must be run on both client and server.

A config file will be automatically generated in profiles/Zenarchist/ZenVeganConfig.json where you can specify the chance to spawn as a vegan, the stamina multiplier vegans get (optional), the text notifications they receive (optional) and the list of foods they cannot eat.

Here's a brief explanation of the JSON settings:

"ConfigVersion": "1.29.1", // Don't touch
"ChanceToSpawnAsVegan": 0.1, // Chance for a new fresh-spawn to be vegan
"VeganStaminaRecoveryMulti": 1.5, // Stamina recovery multiplier for vegans (set to 1.0 or 0.0 to disable buff)
"CanUseFruitOnTreeToVeganize": 0, // Allow players to use fruit on any tree to become vegan (irreversible - off by default) 
"NotifyVeganText": "#STR_ZenVeganism_Notification", // The text notification players get when spawning to notify them they're vegan
"NotifyCantEatText": "#STR_ZenVeganism_Yuck", // The text notification players get when trying to eat meat
"CantEatList": [] // A text list of items a vegan player cannot eat without vomiting

[h1]Repack & Source Code:[/h1]

You can repack this mod if you like, and do anything else you want with it for that matter. Just keep in mind my future updates won't be applied so make sure to check back for new versions if you notice any bugs. The source code is on my GitHub at www.zenarchist.com

[h1]Learn Modding[/h1]

Want to learn how to make your own mods? Check out my guides on YouTube: https://www.youtube.com/@Zenarchist

[h1]Buy Me A Coffee:[/h1]

All my mods are free and open source, but it takes an enormous amount of time to put some of these mods together. If I've helped you out, please consider helping me buy my next coffee! I don't expect it, but I very much appreciate it.

https://buymeacoffee.com/zenarchist

Enjoy