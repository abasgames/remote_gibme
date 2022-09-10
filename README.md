# Remote Gibme

A [SvenMod](https://github.com/sw1ft747/svenmod) plugin

## What

You gib when someone sends `!remotegib` or `|remotegib` in chat

## Why

Fun

## How

### Install

1. Download `remote_gibme.dll` from [Releases](https://github.com/Noxturnix/remote_gibme/releases)
2. Move the file to `Sven Co-op\svenmod\plugins\remote_gibme.dll`
3. Edit `Sven Co-op\svenmod\plugins.txt`

```
"Plugins"
{
    ...
    "remote_gibme" "1"
}
```

### Stop the plugin without restarting the game

1. In console, enter `sm plugins list`
2. Find `"Remote Gibme"` and note the plugin index
3. Enter `sm plugins unload <plugin index>`

To load the plugin again, just enter `sm plugins load remote_gibme`

# Credit

- Boilerplate code from SvenMod's [sample_plugin](https://github.com/sw1ft747/svenmod/tree/main/sample_plugin)
- Helps from Sw1ft

# License

[DO WHAT THE F\*CK YOU WANT TO](LICENSE)
