This write-up is for the To C or not to C programming challenge

The goal of this challenge was to implement the gteline() function for the hamlet player, if this function could be implemented correctly, then when the program would run it would output the flag. A template was given with the parameters to the function and the rest of the program.

First I validate whether the parameters are valid
```C
    // Validate input parameters
    if (!play || act < 1 || scene < 1 || line_number < 0) {
        return NULL;
    }
```
I then check if the act exists then grab that act
```C
    // Check if the requested act exists 
    if (act > play->num_acts) {
        return NULL;
    }
    
    // Get the requested act
    Act *target_act = &play->acts[act - 1];
```
Next I  check if the scene exists and then iterate throught eh scene tabel to find it
```C
    // Check if the requested scene exists 
    if (scene > target_act->num_scenes) {
        return NULL;
    }
    
    // Navigate to the scene table
    uint8_t *scene_table = (uint8_t *)play + play->scene_table_offset;
    
    // Navigate to the first scene of this act
    Scene *current_scene = (Scene *)(scene_table + target_act->first_scene_offset);
    
    // Find the requested scene by iterating through scenes in this act
    for (uint32_t i = 0; i < scene; i++) {
        // Move to the next scene using the size field
        current_scene = (Scene *)((uint8_t *)current_scene + current_scene->size);
    }
```
I then check if the line exists and then find the line and return it
```C
    // Check if the requested line exists 
    if (line_number >= current_scene->num_lines) {
        return NULL;
    }
    
    // Get the requested line
    Line *target_line = &current_scene->lines[line_number];
    
    // Navigate to the string table
    uint8_t *string_table = (uint8_t *)play + play->string_table_offset;
    
    // Navigate to the specific string entry using the text_offset
    StringTableEntry *string_entry = (StringTableEntry *)(string_table + target_line->text_offset);
    
    // Return pointer to the actual text
    return string_entry->text;
}
```

I was able to complete this basic implementation but when I ran the program it would print only random numbers, I then ran it through ChatGPT to debug and got this
I was checking for the scene based on its position instead of the value which would allow me to grab a scene if they are not in order or if a scene is missing, the same issue occured with the line.
```C
#include "play.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char *get_line(Play *play, int act, int scene, int line_number)
{
    // Validate input parameters
    if (!play || act < 1 || scene < 1 || line_number < 0) {
        return NULL;
    }
    
    // Check if the requested act exists 
    if (act > play->num_acts) {
        return NULL;
    }
    
    // Get the requested act
    Act *target_act = &play->acts[act - 1];
    
    // Check if the requested scene exists 
    if (scene > target_act->num_scenes) {
        return NULL;
    }
    
    // Navigate to the scene table
    char *scene_table = (char *)play + play->scene_table_offset;
    
    // Navigate to the first scene of this act
    Scene *current_scene = (Scene *)(scene_table + target_act->first_scene_offset);
    
    // Find the requested scene by number
    for (uint32_t s = 0; s < target_act->num_scenes; s++) {
        if (current_scene->number == scene) {
            
            // Search for the requested line by number
            for (uint32_t i = 0; i < current_scene->num_lines; i++) {
                Line *current_line = &current_scene->lines[i];
                
                if (current_line->number == line_number) {
                    // Navigate to the string table
                    char *string_table = (char *)play + play->string_table_offset;
                    
                    // Navigate to the specific string entry
                    StringTableEntry *string_entry = (StringTableEntry *)(string_table + current_line->text_offset);
                    
                    // Return pointer to the actual text
                    return string_entry->text;
                }
            }

            // Line not found in this scene
            return NULL;
        }

        // Move to the next scene using the size field
        current_scene = (Scene *)((char *)current_scene + current_scene->size);
    }

    // Scene not found
    return NULL;
}

```

After running this I was able to get the flag to print

CWE{brevity_is_the_soul_of_wit_ZrhFoEJx}
