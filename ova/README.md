# ova Module for Drupal 8

OVA supports Textfield Formatters
OVA Module is a HTML5-based video & audio player with a built-in Flash fallback for older
browsers. This means that videos and audios can be played on nearly all devices.

## Installation and Configuration.

1. Install the ova module and module path should be '/modules/contrib'. 
2. Enable the module in your module page.
3. create a Textfield 
   Structure -> Content types -> [type] -> Manage fields. Make sure
   the allowed extensions contain only HTML5 video & audio extensions, such as mp4,
   webm,ogg, youtube for video and such as mp3 for audio etc.
4. Choose field formatters like OVA Audio Formatter & OVA Video Formatter for the textfield.
