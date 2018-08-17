# model01-layout
My custom colemak layout for the model 01 keyboard, specialized for the french language.

Also featuring layouts for windows (KLC format) and linux (xkb format) for both the model 01 keyboard and a classic qwerty keyboard.

## Model 01 firmware
The firmware can be built and flash to the keyboard by following instructions from the official wiki :
https://github.com/keyboardio/Kaleidoscope/wiki/Keyboardio-Model-01-Introduction



## Linux installation
Copy the file over the existing xkb us layout and reload the layout.

```
$ sudo cp linux/us-colemak-model01 /usr/share/X11/xkb/symbols/us
$ setxkbmap us
```

The file also includes the layout to be used on a classic QWERTY keyboard.

`$ setxkbmap us -variant colemak`


## Windows installation
Use the KeyboardLayoutCreator from Microsoft to load the file, generate an installer, and install it on the Operating System.
