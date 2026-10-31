# The Bon Odori 事件时间轴 (`games/bon_odori/bon_odori.bs`)

> 由脚本静态展开 `call` / `goto` / `loop` 自动生成。
>
> * **tick**：beatscript 时间单位，`rest N` 即 N tick；**24 tick = 1 拍**，**96 tick = 1 小节 (4/4)**。
> * **小节:拍**：从 0 tick 起算，第 1 小节第 1 拍 = `1:1`。
> * **时间**：按当时 `set_tempo` 估算（入口 124 BPM，练习/正篇 121 BPM），仅作参考。
> * 除 `rest` 外所有命令都是**同 tick 瞬时执行**，因此同一时刻可能有多条事件。
> * 练习段的 `loop_end` 前提是玩家**没有**抢拍失误；一旦 `bon_odori_stop_input_check` 检测到抢拍会调 `beatscript_enable_loops()`，该段会重新循环一遍。

## 总览

| 区段 | 起始 tick | 结束 tick | 时长 (tick) | 时长 (小节) | 起始时间 |
|---|---:|---:|---:|---:|---:|
| 入口 / 前奏 (Entry + Prologue) | 0 | 240 | 240 | 2.5 | 0:00.00 |
| 练习模式 (Practice) | 240 | 2208 | 1968 | 20.5 | 0:04.84 |
| 正篇 (Main) | 2208 | 7632 | 5424 | 56.5 | 0:45.50 |
| **合计** | 0 | 7632 | 7632 | 79.5 | 2:37.57 |

## 1. 入口 / 前奏 / 收尾

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 1 | 0 | 1:1 | 0:00.00 | `set_tempo 124` |
| 2 | 24 | 1:2 | 0:00.48 | `set_game_fade_in_time 8` |
| 3 | 24 | 1:2 | 0:00.48 | `load_game bon_odori_prologue_engine, 0` |
| 4 | 24 | 1:2 | 0:00.48 | `run stop_all_soundplayers` |
| 5 | 48 | 1:3 | 0:00.97 | `play_sfx s_jingle_bon_seqData` |
| 6 | 96 | 2:1 | 0:01.94 | `run func_080454e0, 5` |
| 7 | 216 | 3:2 | 0:04.35 | `run func_08006d80, 0` |
| 8 | 240 | 3:3 | 0:04.84 | `set_game_fade_in_time 16` |
| 9 | 240 | 3:3 | 0:04.84 | `set_game_fade_in_time 16` |
| 10 | 240 | 3:3 | 0:04.84 | `load_bon_odori` |
| 11 | 240 | 3:3 | 0:04.84 | `enable_play_inputs` |
| 12 | 240 | 3:3 | 0:04.84 | `start_tracking_inputs` |
| 13 | 7584 | 80:1 | 2:36.57 | `disable_pause_menu` |
| 14 | 7584 | 80:1 | 2:36.57 | `disable_play_inputs` |
| 15 | 7584 | 80:1 | 2:36.57 | `fade_music_out 48` |
| 16 | 7584 | 80:1 | 2:36.57 | `fade_screen_out 12, BLACK` |
| 17 | 7632 | 80:3 | 2:37.57 | `stop` (脚本结束) |

## 2. 练习模式

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 18 | 240 | 3:3 | 0:04.84 | `stop_tracking_inputs` |
| 19 | 240 | 3:3 | 0:04.84 | `set_tempo 121` |
| 20 | 264 | 3:4 | 0:05.33 | `enable_pause_menu` |
| 21 | 288 | 4:1 | 0:05.83 | `set_music_volume 150` |
| 22 | 288 | 4:1 | 0:05.83 | `play_music s_mario2_seqData` |
| 23 | 288 | 4:1 | 0:05.83 | `stop_tracking_inputs` |
| 24 | 288 | 4:1 | 0:05.83 | `run gameplay_display_skip_icon, 1` |
| 25 | 288 | 4:1 | 0:05.83 | `run gameplay_set_tutorial scene_bon_odori_skipped_practice` |
| 26 | 384 | 5:1 | 0:07.81 | `bon_odori_lyrics_print_center 1, D_08067a84` |
| 27 | 480 | 6:1 | 0:09.80 | `bon_odori_lyrics_clear_line 1` |
| 28 | 528 | 6:3 | 0:10.79 | `bon_odori_lyrics_print_center 1, D_08067aa4` |
| 29 | 720 | 8:3 | 0:14.76 | `bon_odori_lyrics_clear_line 1` |
| 30 | 768 | 9:1 | 0:15.75 | `bon_odori_darken_screen 48` |
| 31 | 768 | 9:1 | 0:15.75 | `bon_odori_lyrics_print_left 0, text_bon_odori_don_don_pan_pan_2` |
| 32 | 768 | 9:1 | 0:15.75 | `bon_odori_lyrics_print_right 1, text_bon_odori_dondo_pan_pan` |
| 33 | 852 | 9:4.5 | 0:17.48 | `run gameplay_reset_loop_counter` |
| 34 | 852 | 9:4.5 | 0:17.48 | `bon_odori_start_input_check` |
| 35 | 852 | 9:4.5 | 0:17.48 | `switch_loop_counter` -> case 0 (首轮，default 分支跳过) |
| 36 | 852 | 9:4.5 | 0:17.48 | `play_sfx s_bon_dondon1_seqData` |
| 37 | 864 | 10:1 | 0:17.73 | `bon_odori_animate_all ANIM_BOW` |
| 38 | 864 | 10:1 | 0:17.73 | `bon_odori_lyrics_start_highlight 0, 88` |
| 39 | 888 | 10:2 | 0:18.23 | `spawn_cue CUE_FORWARD_CLAP` |
| 40 | 912 | 10:3 | 0:18.72 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 41 | 912 | 10:3 | 0:18.72 | `spawn_cue CUE_FORWARD_CLAP` |
| 42 | 912 | 10:3 | 0:18.72 | `beat_anim` |
| 43 | 936 | 10:4 | 0:19.22 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 44 | 960 | 11:1 | 0:19.71 | `bon_odori_lyrics_start_highlight 1, 54` |
| 45 | 960 | 11:1 | 0:19.71 | `spawn_cue CUE_FORWARD_CLAP` |
| 46 | 984 | 11:2 | 0:20.21 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 47 | 984 | 11:2 | 0:20.21 | `spawn_cue CUE_FORWARD_CLAP` |
| 48 | 1008 | 11:3 | 0:20.71 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 49 | 1008 | 11:3 | 0:20.71 | `beat_anim` |
| 50 | 1032 | 11:4 | 0:21.20 | `bon_odori_lyrics_clear_line 0` |
| 51 | 1032 | 11:4 | 0:21.20 | `bon_odori_lyrics_clear_line 1` |
| 52 | 1044 | 11:4.5 | 0:21.45 | `bon_odori_lyrics_print_left 0, text_bon_odori_don_don_pan_pan_2` |
| 53 | 1044 | 11:4.5 | 0:21.45 | `bon_odori_lyrics_print_right 1, text_bon_odori_dondo_pan_pan` |
| 54 | 1044 | 11:4.5 | 0:21.45 | `play_sfx s_bon_dondon1_seqData` |
| 55 | 1056 | 12:1 | 0:21.70 | `bon_odori_animate_all ANIM_BOW` |
| 56 | 1056 | 12:1 | 0:21.70 | `bon_odori_lyrics_start_highlight 0, 88` |
| 57 | 1080 | 12:2 | 0:22.19 | `spawn_cue CUE_FORWARD_CLAP` |
| 58 | 1104 | 12:3 | 0:22.69 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 59 | 1104 | 12:3 | 0:22.69 | `spawn_cue CUE_FORWARD_CLAP` |
| 60 | 1104 | 12:3 | 0:22.69 | `beat_anim` |
| 61 | 1128 | 12:4 | 0:23.19 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 62 | 1152 | 13:1 | 0:23.68 | `bon_odori_lyrics_start_highlight 1, 54` |
| 63 | 1152 | 13:1 | 0:23.68 | `spawn_cue CUE_FORWARD_CLAP` |
| 64 | 1176 | 13:2 | 0:24.18 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 65 | 1176 | 13:2 | 0:24.18 | `spawn_cue CUE_FORWARD_CLAP` |
| 66 | 1200 | 13:3 | 0:24.67 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 67 | 1200 | 13:3 | 0:24.67 | `beat_anim` |
| 68 | 1224 | 13:4 | 0:25.17 | `bon_odori_lyrics_clear_line 0` |
| 69 | 1224 | 13:4 | 0:25.17 | `bon_odori_lyrics_clear_line 1` |
| 70 | 1236 | 13:4.5 | 0:25.42 | `bon_odori_stop_input_check` |
| 71 | 1236 | 13:4.5 | 0:25.42 | `run gameplay_increment_loop_counter` |
| 72 | 1248 | 14:1 | 0:25.67 | `bon_odori_lighten_screen 48` |
| 73 | 1248 | 14:1 | 0:25.67 | `bon_odori_lyrics_print_center 1, D_08067ad0` |
| 74 | 1296 | 14:3 | 0:26.66 | `bon_odori_lyrics_clear_line 1` |
| 75 | 1320 | 14:4 | 0:27.15 | `bon_odori_lyrics_print_center 1, D_08067adc` |
| 76 | 1488 | 16:3 | 0:30.62 | `bon_odori_lyrics_clear_line 1` |
| 77 | 1536 | 17:1 | 0:31.62 | `bon_odori_darken_screen 48` |
| 78 | 1536 | 17:1 | 0:31.62 | `bon_odori_lyrics_print_left 0, text_bon_odori_dondo_panpa` |
| 79 | 1536 | 17:1 | 0:31.62 | `bon_odori_lyrics_print_center 1, text_bon_odori_dondo_panpa` |
| 80 | 1536 | 17:1 | 0:31.62 | `bon_odori_lyrics_print_right 2, text_bon_odori_don_pan_pan` |
| 81 | 1620 | 17:4.5 | 0:33.35 | `run gameplay_reset_loop_counter` |
| 82 | 1620 | 17:4.5 | 0:33.35 | `bon_odori_start_input_check` |
| 83 | 1620 | 17:4.5 | 0:33.35 | `switch_loop_counter` -> case 0 (首轮，default 分支跳过) |
| 84 | 1620 | 17:4.5 | 0:33.35 | `play_sfx s_bon_dondon2_seqData` |
| 85 | 1632 | 18:1 | 0:33.60 | `bon_odori_lyrics_start_highlight 0, 45` |
| 86 | 1632 | 18:1 | 0:33.60 | `spawn_cue CUE_SIDE_CLAP` |
| 87 | 1648 | 18:1.667 | 0:33.93 | `spawn_cue CUE_SIDE_CLAP` |
| 88 | 1656 | 18:2 | 0:34.09 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 89 | 1656 | 18:2 | 0:34.09 | `beat_anim` |
| 90 | 1672 | 18:2.667 | 0:34.43 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 91 | 1680 | 18:3 | 0:34.59 | `bon_odori_lyrics_start_highlight 1, 45` |
| 92 | 1680 | 18:3 | 0:34.59 | `spawn_cue CUE_SIDE_CLAP` |
| 93 | 1696 | 18:3.667 | 0:34.92 | `spawn_cue CUE_SIDE_CLAP` |
| 94 | 1704 | 18:4 | 0:35.09 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 95 | 1704 | 18:4 | 0:35.09 | `beat_anim` |
| 96 | 1720 | 18:4.667 | 0:35.42 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 97 | 1728 | 19:1 | 0:35.58 | `bon_odori_animate_all ANIM_BOW` |
| 98 | 1728 | 19:1 | 0:35.58 | `bon_odori_lyrics_start_highlight 2, 60` |
| 99 | 1728 | 19:1 | 0:35.58 | `spawn_cue CUE_FORWARD_CLAP` |
| 100 | 1752 | 19:2 | 0:36.08 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 101 | 1752 | 19:2 | 0:36.08 | `spawn_cue CUE_FORWARD_CLAP` |
| 102 | 1776 | 19:3 | 0:36.57 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 103 | 1776 | 19:3 | 0:36.57 | `beat_anim` |
| 104 | 1800 | 19:4 | 0:37.07 | `bon_odori_lyrics_clear_line 0` |
| 105 | 1800 | 19:4 | 0:37.07 | `bon_odori_lyrics_clear_line 1` |
| 106 | 1800 | 19:4 | 0:37.07 | `bon_odori_lyrics_clear_line 2` |
| 107 | 1812 | 19:4.5 | 0:37.32 | `bon_odori_lyrics_print_left 0, text_bon_odori_dondo_panpa` |
| 108 | 1812 | 19:4.5 | 0:37.32 | `bon_odori_lyrics_print_center 1, text_bon_odori_dondo_panpa` |
| 109 | 1812 | 19:4.5 | 0:37.32 | `bon_odori_lyrics_print_right 2, text_bon_odori_don_pan_pan` |
| 110 | 1812 | 19:4.5 | 0:37.32 | `play_sfx s_bon_dondon2_seqData` |
| 111 | 1824 | 20:1 | 0:37.57 | `bon_odori_lyrics_start_highlight 0, 45` |
| 112 | 1824 | 20:1 | 0:37.57 | `spawn_cue CUE_SIDE_CLAP` |
| 113 | 1840 | 20:1.667 | 0:37.90 | `spawn_cue CUE_SIDE_CLAP` |
| 114 | 1848 | 20:2 | 0:38.06 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 115 | 1848 | 20:2 | 0:38.06 | `beat_anim` |
| 116 | 1864 | 20:2.667 | 0:38.39 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 117 | 1872 | 20:3 | 0:38.56 | `bon_odori_lyrics_start_highlight 1, 45` |
| 118 | 1872 | 20:3 | 0:38.56 | `spawn_cue CUE_SIDE_CLAP` |
| 119 | 1888 | 20:3.667 | 0:38.89 | `spawn_cue CUE_SIDE_CLAP` |
| 120 | 1896 | 20:4 | 0:39.05 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 121 | 1896 | 20:4 | 0:39.05 | `beat_anim` |
| 122 | 1912 | 20:4.667 | 0:39.38 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 123 | 1920 | 21:1 | 0:39.55 | `bon_odori_animate_all ANIM_BOW` |
| 124 | 1920 | 21:1 | 0:39.55 | `bon_odori_lyrics_start_highlight 2, 60` |
| 125 | 1920 | 21:1 | 0:39.55 | `spawn_cue CUE_FORWARD_CLAP` |
| 126 | 1944 | 21:2 | 0:40.05 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 127 | 1944 | 21:2 | 0:40.05 | `spawn_cue CUE_FORWARD_CLAP` |
| 128 | 1968 | 21:3 | 0:40.54 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 129 | 1968 | 21:3 | 0:40.54 | `beat_anim` |
| 130 | 1992 | 21:4 | 0:41.04 | `bon_odori_lyrics_clear_line 0` |
| 131 | 1992 | 21:4 | 0:41.04 | `bon_odori_lyrics_clear_line 1` |
| 132 | 1992 | 21:4 | 0:41.04 | `bon_odori_lyrics_clear_line 2` |
| 133 | 2004 | 21:4.5 | 0:41.28 | `bon_odori_stop_input_check` |
| 134 | 2004 | 21:4.5 | 0:41.28 | `run gameplay_increment_loop_counter` |
| 135 | 2016 | 22:1 | 0:41.53 | `run gameplay_set_tutorial NULL` |
| 136 | 2016 | 22:1 | 0:41.53 | `mod_music_volume 60, 168` |
| 137 | 2016 | 22:1 | 0:41.53 | `bon_odori_lighten_screen 48` |
| 138 | 2016 | 22:1 | 0:41.53 | `bon_odori_lyrics_print_center 1, D_08067ad0` |
| 139 | 2064 | 22:3 | 0:42.52 | `bon_odori_lyrics_clear_line 1` |
| 140 | 2088 | 22:4 | 0:43.02 | `bon_odori_lyrics_print_center 1, D_08067b00` |

## 3. 正篇

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 141 | 2208 | 24:1 | 0:45.50 | `set_results_header D_08067778` |
| 142 | 2208 | 24:1 | 0:45.50 | `import_marking_criteria bon_odori_marking_criteria` |
| 143 | 2208 | 24:1 | 0:45.50 | `run gameplay_set_mercy_count, 1` |
| 144 | 2208 | 24:1 | 0:45.50 | `start_tracking_inputs` |
| 145 | 2208 | 24:1 | 0:45.50 | `set_tempo 121` |
| 146 | 2208 | 24:1 | 0:45.50 | `set_music_volume 256` |
| 147 | 2208 | 24:1 | 0:45.50 | `play_music s_bon_odori_bgm_seqData` |
| 148 | 2304 | 25:1 | 0:47.48 | `bon_odori_lyrics_clear_line 1` |
| 149 | 2376 | 25:4 | 0:48.97 | `beat_anim` |
| 150 | 2400 | 26:1 | 0:49.47 | `beat_anim` |
| 151 | 2424 | 26:2 | 0:49.96 | `beat_anim` |
| 152 | 2448 | 26:3 | 0:50.46 | `beat_anim` |
| 153 | 2472 | 26:4 | 0:50.95 | `beat_anim` |
| 154 | 2496 | 27:1 | 0:51.45 | `beat_anim` |
| 155 | 2520 | 27:2 | 0:51.95 | `beat_anim` |
| 156 | 2544 | 27:3 | 0:52.44 | `beat_anim` |
| 157 | 2568 | 27:4 | 0:52.94 | `beat_anim` |
| 158 | 2592 | 28:1 | 0:53.43 | `bon_odori_animate_all ANIM_BOW` |
| 159 | 2592 | 28:1 | 0:53.43 | `beat_anim` |
| 160 | 2616 | 28:2 | 0:53.93 | `beat_anim` |
| 161 | 2640 | 28:3 | 0:54.43 | `beat_anim` |
| 162 | 2688 | 29:1 | 0:55.42 | `start_perfect_campaign` |
| 163 | 2688 | 29:1 | 0:55.42 | `beat_anim` |
| 164 | 2712 | 29:2 | 0:55.91 | `beat_anim` |
| 165 | 2736 | 29:3 | 0:56.41 | `beat_anim` |
| 166 | 2760 | 29:4 | 0:56.90 | `beat_anim` |
| 167 | 2784 | 30:1 | 0:57.40 | `beat_anim` |
| 168 | 2808 | 30:2 | 0:57.90 | `beat_anim` |
| 169 | 2832 | 30:3 | 0:58.39 | `bon_odori_animate_all ANIM_BOW` |
| 170 | 2832 | 30:3 | 0:58.39 | `beat_anim` |
| 171 | 2856 | 30:4 | 0:58.89 | `bon_odori_darken_screen 48` |
| 172 | 2856 | 30:4 | 0:58.89 | `start_perfect_campaign` |

### 段落起点: tick 2856 / 第 30 小节 / 4  (0:58.89)

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 173 | 2856 | 30:4 | 0:58.89 | `set_marking_criteria 0` |
| 174 | 2856 | 30:4 | 0:58.89 | `bon_odori_lyrics_print_left 0, text_bon_odori_ha` |
| 175 | 2856 | 30:4 | 0:58.89 | `bon_odori_lyrics_print_center 1, text_bon_odori_hanabi_agare_ba` |
| 176 | 2856 | 30:4 | 0:58.89 | `beat_anim` |
| 177 | 2880 | 31:1 | 0:59.38 | `bon_odori_lyrics_clear_line 2` |
| 178 | 2880 | 31:1 | 0:59.38 | `bon_odori_lyrics_clear_line 3` |
| 179 | 2880 | 31:1 | 0:59.38 | `bon_odori_lyrics_start_highlight 0, 93` |
| 180 | 2880 | 31:1 | 0:59.38 | `beat_anim` |
| 181 | 2904 | 31:2 | 0:59.88 | `beat_anim` |
| 182 | 2928 | 31:3 | 1:00.38 | `beat_anim` |
| 183 | 2952 | 31:4 | 1:00.87 | `beat_anim` |
| 184 | 2976 | 32:1 | 1:01.37 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 185 | 2976 | 32:1 | 1:01.37 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 186 | 2976 | 32:1 | 1:01.37 | `bon_odori_lyrics_start_highlight 1, 93` |
| 187 | 2976 | 32:1 | 1:01.37 | `beat_anim` |
| 188 | 3000 | 32:2 | 1:01.86 | `beat_anim` |
| 189 | 3024 | 32:3 | 1:02.36 | `beat_anim` |
| 190 | 3048 | 32:4 | 1:02.86 | `beat_anim` |
| 191 | 3072 | 33:1 | 1:03.35 | `bon_odori_start_input_check` |
| 192 | 3072 | 33:1 | 1:03.35 | `bon_odori_lyrics_start_highlight 2, 88` |
| 193 | 3072 | 33:1 | 1:03.35 | `bon_odori_animate_all ANIM_BOW` |
| 194 | 3072 | 33:1 | 1:03.35 | `beat_anim` |
| 195 | 3096 | 33:2 | 1:03.85 | `spawn_cue CUE_SIDE_CLAP` |
| 196 | 3096 | 33:2 | 1:03.85 | `beat_anim` |
| 197 | 3120 | 33:3 | 1:04.34 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 198 | 3120 | 33:3 | 1:04.34 | `spawn_cue CUE_SIDE_CLAP` |
| 199 | 3120 | 33:3 | 1:04.34 | `beat_anim` |
| 200 | 3144 | 33:4 | 1:04.84 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 201 | 3144 | 33:4 | 1:04.84 | `beat_anim` |
| 202 | 3168 | 34:1 | 1:05.33 | `bon_odori_lyrics_clear_line 0` |
| 203 | 3168 | 34:1 | 1:05.33 | `bon_odori_lyrics_clear_line 1` |
| 204 | 3168 | 34:1 | 1:05.33 | `bon_odori_lyrics_start_highlight 3, 54` |
| 205 | 3168 | 34:1 | 1:05.33 | `spawn_cue CUE_FORWARD_CLAP` |
| 206 | 3168 | 34:1 | 1:05.33 | `beat_anim` |
| 207 | 3192 | 34:2 | 1:05.83 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 208 | 3192 | 34:2 | 1:05.83 | `spawn_cue CUE_FORWARD_CLAP` |
| 209 | 3192 | 34:2 | 1:05.83 | `beat_anim` |
| 210 | 3216 | 34:3 | 1:06.33 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 211 | 3216 | 34:3 | 1:06.33 | `beat_anim` |
| 212 | 3240 | 34:4 | 1:06.82 | `bon_odori_stop_input_check` |
| 213 | 3240 | 34:4 | 1:06.82 | `bon_odori_lyrics_print_left 0, text_bon_odori_haa` |
| 214 | 3240 | 34:4 | 1:06.82 | `bon_odori_lyrics_print_center 1, text_bon_odori_kansei_agaru` |
| 215 | 3240 | 34:4 | 1:06.82 | `beat_anim` |
| 216 | 3264 | 35:1 | 1:07.32 | `bon_odori_lyrics_clear_line 2` |
| 217 | 3264 | 35:1 | 1:07.32 | `bon_odori_lyrics_clear_line 3` |
| 218 | 3264 | 35:1 | 1:07.32 | `bon_odori_lyrics_start_highlight 0, 93` |
| 219 | 3264 | 35:1 | 1:07.32 | `beat_anim` |
| 220 | 3288 | 35:2 | 1:07.81 | `beat_anim` |
| 221 | 3312 | 35:3 | 1:08.31 | `beat_anim` |
| 222 | 3336 | 35:4 | 1:08.81 | `beat_anim` |
| 223 | 3360 | 36:1 | 1:09.30 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 224 | 3360 | 36:1 | 1:09.30 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 225 | 3360 | 36:1 | 1:09.30 | `bon_odori_lyrics_start_highlight 1, 93` |
| 226 | 3360 | 36:1 | 1:09.30 | `beat_anim` |
| 227 | 3384 | 36:2 | 1:09.80 | `beat_anim` |
| 228 | 3408 | 36:3 | 1:10.29 | `beat_anim` |
| 229 | 3432 | 36:4 | 1:10.79 | `beat_anim` |
| 230 | 3456 | 37:1 | 1:11.28 | `bon_odori_start_input_check` |
| 231 | 3456 | 37:1 | 1:11.28 | `bon_odori_lyrics_start_highlight 2, 88` |
| 232 | 3456 | 37:1 | 1:11.28 | `bon_odori_animate_all ANIM_BOW` |
| 233 | 3456 | 37:1 | 1:11.28 | `beat_anim` |
| 234 | 3480 | 37:2 | 1:11.78 | `spawn_cue CUE_SIDE_CLAP` |
| 235 | 3480 | 37:2 | 1:11.78 | `beat_anim` |
| 236 | 3504 | 37:3 | 1:12.28 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 237 | 3504 | 37:3 | 1:12.28 | `spawn_cue CUE_SIDE_CLAP` |
| 238 | 3504 | 37:3 | 1:12.28 | `beat_anim` |
| 239 | 3528 | 37:4 | 1:12.77 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 240 | 3528 | 37:4 | 1:12.77 | `beat_anim` |
| 241 | 3552 | 38:1 | 1:13.27 | `bon_odori_lyrics_clear_line 0` |
| 242 | 3552 | 38:1 | 1:13.27 | `bon_odori_lyrics_clear_line 1` |
| 243 | 3552 | 38:1 | 1:13.27 | `bon_odori_lyrics_start_highlight 3, 54` |
| 244 | 3552 | 38:1 | 1:13.27 | `spawn_cue CUE_FORWARD_CLAP` |
| 245 | 3552 | 38:1 | 1:13.27 | `beat_anim` |
| 246 | 3576 | 38:2 | 1:13.76 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 247 | 3576 | 38:2 | 1:13.76 | `spawn_cue CUE_FORWARD_CLAP` |
| 248 | 3576 | 38:2 | 1:13.76 | `beat_anim` |
| 249 | 3600 | 38:3 | 1:14.26 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 250 | 3600 | 38:3 | 1:14.26 | `beat_anim` |
| 251 | 3624 | 38:4 | 1:14.76 | `bon_odori_stop_input_check` |
| 252 | 3624 | 38:4 | 1:14.76 | `bon_odori_lyrics_print_left 0, text_bon_odori_ha` |
| 253 | 3624 | 38:4 | 1:14.76 | `bon_odori_lyrics_print_center 1, text_bon_odori_ninki_agare_ba` |
| 254 | 3624 | 38:4 | 1:14.76 | `beat_anim` |
| 255 | 3648 | 39:1 | 1:15.25 | `bon_odori_lyrics_clear_line 2` |
| 256 | 3648 | 39:1 | 1:15.25 | `bon_odori_lyrics_clear_line 3` |
| 257 | 3648 | 39:1 | 1:15.25 | `bon_odori_lyrics_start_highlight 0, 93` |
| 258 | 3648 | 39:1 | 1:15.25 | `beat_anim` |
| 259 | 3672 | 39:2 | 1:15.75 | `beat_anim` |
| 260 | 3696 | 39:3 | 1:16.24 | `beat_anim` |
| 261 | 3720 | 39:4 | 1:16.74 | `beat_anim` |
| 262 | 3744 | 40:1 | 1:17.24 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 263 | 3744 | 40:1 | 1:17.24 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 264 | 3744 | 40:1 | 1:17.24 | `bon_odori_lyrics_start_highlight 1, 93` |
| 265 | 3744 | 40:1 | 1:17.24 | `beat_anim` |
| 266 | 3768 | 40:2 | 1:17.73 | `beat_anim` |
| 267 | 3792 | 40:3 | 1:18.23 | `beat_anim` |
| 268 | 3816 | 40:4 | 1:18.72 | `beat_anim` |
| 269 | 3840 | 41:1 | 1:19.22 | `bon_odori_start_input_check` |
| 270 | 3840 | 41:1 | 1:19.22 | `bon_odori_lyrics_start_highlight 2, 88` |
| 271 | 3840 | 41:1 | 1:19.22 | `bon_odori_animate_all ANIM_BOW` |
| 272 | 3840 | 41:1 | 1:19.22 | `beat_anim` |
| 273 | 3864 | 41:2 | 1:19.71 | `spawn_cue CUE_SIDE_CLAP` |
| 274 | 3864 | 41:2 | 1:19.71 | `beat_anim` |
| 275 | 3888 | 41:3 | 1:20.21 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 276 | 3888 | 41:3 | 1:20.21 | `spawn_cue CUE_SIDE_CLAP` |
| 277 | 3888 | 41:3 | 1:20.21 | `beat_anim` |
| 278 | 3912 | 41:4 | 1:20.71 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 279 | 3912 | 41:4 | 1:20.71 | `beat_anim` |
| 280 | 3936 | 42:1 | 1:21.20 | `bon_odori_lyrics_clear_line 0` |
| 281 | 3936 | 42:1 | 1:21.20 | `bon_odori_lyrics_clear_line 1` |
| 282 | 3936 | 42:1 | 1:21.20 | `bon_odori_lyrics_start_highlight 3, 54` |
| 283 | 3936 | 42:1 | 1:21.20 | `spawn_cue CUE_FORWARD_CLAP` |
| 284 | 3936 | 42:1 | 1:21.20 | `beat_anim` |
| 285 | 3960 | 42:2 | 1:21.70 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 286 | 3960 | 42:2 | 1:21.70 | `spawn_cue CUE_FORWARD_CLAP` |
| 287 | 3960 | 42:2 | 1:21.70 | `beat_anim` |
| 288 | 3984 | 42:3 | 1:22.19 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 289 | 3984 | 42:3 | 1:22.19 | `beat_anim` |
| 290 | 4008 | 42:4 | 1:22.69 | `bon_odori_stop_input_check` |
| 291 | 4008 | 42:4 | 1:22.69 | `bon_odori_lyrics_print_left 0, text_bon_odori_haa` |
| 292 | 4008 | 42:4 | 1:22.69 | `bon_odori_lyrics_print_center 1, text_bon_odori_kyuryo_agaru` |
| 293 | 4008 | 42:4 | 1:22.69 | `beat_anim` |
| 294 | 4032 | 43:1 | 1:23.19 | `bon_odori_lyrics_clear_line 2` |
| 295 | 4032 | 43:1 | 1:23.19 | `bon_odori_lyrics_clear_line 3` |
| 296 | 4032 | 43:1 | 1:23.19 | `bon_odori_lyrics_start_highlight 0, 93` |
| 297 | 4032 | 43:1 | 1:23.19 | `beat_anim` |
| 298 | 4056 | 43:2 | 1:23.68 | `beat_anim` |
| 299 | 4080 | 43:3 | 1:24.18 | `beat_anim` |
| 300 | 4104 | 43:4 | 1:24.67 | `beat_anim` |
| 301 | 4128 | 44:1 | 1:25.17 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 302 | 4128 | 44:1 | 1:25.17 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 303 | 4128 | 44:1 | 1:25.17 | `bon_odori_lyrics_start_highlight 1, 93` |
| 304 | 4128 | 44:1 | 1:25.17 | `beat_anim` |
| 305 | 4152 | 44:2 | 1:25.67 | `beat_anim` |
| 306 | 4176 | 44:3 | 1:26.16 | `beat_anim` |
| 307 | 4200 | 44:4 | 1:26.66 | `beat_anim` |
| 308 | 4224 | 45:1 | 1:27.15 | `bon_odori_start_input_check` |
| 309 | 4224 | 45:1 | 1:27.15 | `bon_odori_lyrics_start_highlight 2, 88` |
| 310 | 4224 | 45:1 | 1:27.15 | `bon_odori_animate_all ANIM_BOW` |
| 311 | 4224 | 45:1 | 1:27.15 | `beat_anim` |
| 312 | 4248 | 45:2 | 1:27.65 | `spawn_cue CUE_SIDE_CLAP` |
| 313 | 4248 | 45:2 | 1:27.65 | `beat_anim` |
| 314 | 4272 | 45:3 | 1:28.14 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 315 | 4272 | 45:3 | 1:28.14 | `spawn_cue CUE_SIDE_CLAP` |
| 316 | 4272 | 45:3 | 1:28.14 | `beat_anim` |
| 317 | 4296 | 45:4 | 1:28.64 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 318 | 4296 | 45:4 | 1:28.64 | `beat_anim` |
| 319 | 4320 | 46:1 | 1:29.14 | `bon_odori_lyrics_clear_line 0` |
| 320 | 4320 | 46:1 | 1:29.14 | `bon_odori_lyrics_clear_line 1` |
| 321 | 4320 | 46:1 | 1:29.14 | `bon_odori_lyrics_start_highlight 3, 54` |
| 322 | 4320 | 46:1 | 1:29.14 | `spawn_cue CUE_FORWARD_CLAP` |
| 323 | 4320 | 46:1 | 1:29.14 | `beat_anim` |
| 324 | 4344 | 46:2 | 1:29.63 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 325 | 4344 | 46:2 | 1:29.63 | `spawn_cue CUE_FORWARD_CLAP` |
| 326 | 4344 | 46:2 | 1:29.63 | `beat_anim` |
| 327 | 4368 | 46:3 | 1:30.13 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 328 | 4368 | 46:3 | 1:30.13 | `beat_anim` |
| 329 | 4392 | 46:4 | 1:30.62 | `bon_odori_stop_input_check` |
| 330 | 4392 | 46:4 | 1:30.62 | `bon_odori_lyrics_print_left 1, text_bon_odori_matsuri_da_wasshoi` |
| 331 | 4392 | 46:4 | 1:30.62 | `beat_anim` |
| 332 | 4416 | 47:1 | 1:31.12 | `bon_odori_lyrics_clear_line 2` |
| 333 | 4416 | 47:1 | 1:31.12 | `bon_odori_lyrics_clear_line 3` |
| 334 | 4416 | 47:1 | 1:31.12 | `bon_odori_lyrics_start_highlight 1, 93` |
| 335 | 4416 | 47:1 | 1:31.12 | `beat_anim` |
| 336 | 4440 | 47:2 | 1:31.62 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_panpa_dondo_panpa` |
| 337 | 4440 | 47:2 | 1:31.62 | `beat_anim` |
| 338 | 4464 | 47:3 | 1:32.11 | `beat_anim` |
| 339 | 4488 | 47:4 | 1:32.61 | `beat_anim` |
| 340 | 4512 | 48:1 | 1:33.10 | `bon_odori_start_input_check` |
| 341 | 4512 | 48:1 | 1:33.10 | `bon_odori_animate_all ANIM_BOW` |
| 342 | 4512 | 48:1 | 1:33.10 | `bon_odori_lyrics_start_highlight 3, 86` |
| 343 | 4512 | 48:1 | 1:33.10 | `spawn_cue CUE_SIDE_CLAP` |
| 344 | 4512 | 48:1 | 1:33.10 | `beat_anim` |
| 345 | 4528 | 48:1.667 | 1:33.43 | `spawn_cue CUE_SIDE_CLAP` |
| 346 | 4536 | 48:2 | 1:33.60 | `bon_odori_lyrics_clear_line 1` |
| 347 | 4536 | 48:2 | 1:33.60 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 348 | 4536 | 48:2 | 1:33.60 | `beat_anim` |
| 349 | 4552 | 48:2.667 | 1:33.93 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 350 | 4560 | 48:3 | 1:34.09 | `spawn_cue CUE_SIDE_CLAP` |
| 351 | 4560 | 48:3 | 1:34.09 | `beat_anim` |
| 352 | 4576 | 48:3.667 | 1:34.43 | `spawn_cue CUE_SIDE_CLAP` |
| 353 | 4584 | 48:4 | 1:34.59 | `bon_odori_lyrics_print_left 1, text_bon_odori_nippon_chu_ga_wasshoi` |
| 354 | 4584 | 48:4 | 1:34.59 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 355 | 4584 | 48:4 | 1:34.59 | `beat_anim` |
| 356 | 4600 | 48:4.667 | 1:34.92 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 357 | 4608 | 49:1 | 1:35.09 | `bon_odori_stop_input_check` |
| 358 | 4608 | 49:1 | 1:35.09 | `bon_odori_lyrics_clear_line 3` |
| 359 | 4608 | 49:1 | 1:35.09 | `bon_odori_lyrics_start_highlight 1, 93` |
| 360 | 4608 | 49:1 | 1:35.09 | `beat_anim` |
| 361 | 4632 | 49:2 | 1:35.58 | `bon_odori_lyrics_print_right 3, text_bon_odori_don_don_pan` |
| 362 | 4632 | 49:2 | 1:35.58 | `beat_anim` |
| 363 | 4656 | 49:3 | 1:36.08 | `beat_anim` |
| 364 | 4680 | 49:4 | 1:36.57 | `beat_anim` |
| 365 | 4704 | 50:1 | 1:37.07 | `bon_odori_start_input_check` |
| 366 | 4704 | 50:1 | 1:37.07 | `bon_odori_animate_all ANIM_BOW` |
| 367 | 4704 | 50:1 | 1:37.07 | `bon_odori_lyrics_start_highlight 3, 57` |
| 368 | 4704 | 50:1 | 1:37.07 | `beat_anim` |
| 369 | 4728 | 50:2 | 1:37.57 | `bon_odori_lyrics_clear_line 1` |
| 370 | 4728 | 50:2 | 1:37.57 | `spawn_cue CUE_FORWARD_CLAP` |
| 371 | 4728 | 50:2 | 1:37.57 | `beat_anim` |
| 372 | 4752 | 50:3 | 1:38.06 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 373 | 4752 | 50:3 | 1:38.06 | `beat_anim` |
| 374 | 4776 | 50:4 | 1:38.56 | `bon_odori_stop_input_check` |
| 375 | 4776 | 50:4 | 1:38.56 | `bon_odori_lyrics_print_left 1, text_bon_odori_sore_hikkuri_kaette` |
| 376 | 4776 | 50:4 | 1:38.56 | `bon_odori_lyrics_start_highlight 1, 117` |
| 377 | 4776 | 50:4 | 1:38.56 | `beat_anim` |
| 378 | 4800 | 51:1 | 1:39.05 | `bon_odori_lyrics_clear_line 3` |
| 379 | 4800 | 51:1 | 1:39.05 | `beat_anim` |
| 380 | 4824 | 51:2 | 1:39.55 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 381 | 4824 | 51:2 | 1:39.55 | `beat_anim` |
| 382 | 4848 | 51:3 | 1:40.05 | `bon_odori_animate_all ANIM_SPIN` |
| 383 | 4848 | 51:3 | 1:40.05 | `beat_anim` |
| 384 | 4872 | 51:4 | 1:40.54 | `beat_anim` |
| 385 | 4896 | 52:1 | 1:41.04 | `bon_odori_start_input_check` |
| 386 | 4896 | 52:1 | 1:41.04 | `bon_odori_animate_all ANIM_BOW` |
| 387 | 4896 | 52:1 | 1:41.04 | `bon_odori_lyrics_start_highlight 3, 54` |
| 388 | 4896 | 52:1 | 1:41.04 | `spawn_cue CUE_FORWARD_CLAP` |
| 389 | 4896 | 52:1 | 1:41.04 | `beat_anim` |
| 390 | 4920 | 52:2 | 1:41.53 | `bon_odori_lyrics_clear_line 1` |
| 391 | 4920 | 52:2 | 1:41.53 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 392 | 4920 | 52:2 | 1:41.53 | `spawn_cue CUE_FORWARD_CLAP` |
| 393 | 4920 | 52:2 | 1:41.53 | `beat_anim` |
| 394 | 4944 | 52:3 | 1:42.03 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 395 | 4944 | 52:3 | 1:42.03 | `beat_anim` |
| 396 | 4968 | 52:4 | 1:42.52 | `bon_odori_stop_input_check` |
| 397 | 4968 | 52:4 | 1:42.52 | `bon_odori_lyrics_print_left 0, text_bon_odori_ha_bon_odori` |
| 398 | 4968 | 52:4 | 1:42.52 | `beat_anim` |
| 399 | 4992 | 53:1 | 1:43.02 | `bon_odori_lyrics_clear_line 3` |
| 400 | 4992 | 53:1 | 1:43.02 | `bon_odori_lyrics_start_highlight 0, 93` |
| 401 | 4992 | 53:1 | 1:43.02 | `bon_odori_animate_all ANIM_BOW` |
| 402 | 4992 | 53:1 | 1:43.02 | `beat_anim` |
| 403 | 5016 | 53:2 | 1:43.52 | `bon_odori_lyrics_print_left 1, text_bon_odori_dondo_panpa` |
| 404 | 5016 | 53:2 | 1:43.52 | `bon_odori_lyrics_print_center 2, text_bon_odori_dondo_panpa` |
| 405 | 5016 | 53:2 | 1:43.52 | `bon_odori_lyrics_print_right 3, text_bon_odori_don_pan_pan` |
| 406 | 5040 | 53:3 | 1:44.01 | `beat_anim` |
| 407 | 5088 | 54:1 | 1:45.00 | `bon_odori_start_input_check` |
| 408 | 5088 | 54:1 | 1:45.00 | `bon_odori_lyrics_start_highlight 1, 43` |
| 409 | 5088 | 54:1 | 1:45.00 | `spawn_cue CUE_SIDE_CLAP` |
| 410 | 5088 | 54:1 | 1:45.00 | `beat_anim` |
| 411 | 5104 | 54:1.667 | 1:45.33 | `spawn_cue CUE_SIDE_CLAP` |
| 412 | 5112 | 54:2 | 1:45.50 | `bon_odori_lyrics_clear_line 0` |
| 413 | 5112 | 54:2 | 1:45.50 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 414 | 5112 | 54:2 | 1:45.50 | `beat_anim` |
| 415 | 5128 | 54:2.667 | 1:45.83 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 416 | 5136 | 54:3 | 1:46.00 | `bon_odori_lyrics_start_highlight 2, 43` |
| 417 | 5136 | 54:3 | 1:46.00 | `spawn_cue CUE_SIDE_CLAP` |
| 418 | 5136 | 54:3 | 1:46.00 | `beat_anim` |
| 419 | 5152 | 54:3.667 | 1:46.33 | `spawn_cue CUE_SIDE_CLAP` |
| 420 | 5160 | 54:4 | 1:46.49 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 421 | 5160 | 54:4 | 1:46.49 | `beat_anim` |
| 422 | 5176 | 54:4.667 | 1:46.82 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 423 | 5184 | 55:1 | 1:46.99 | `bon_odori_animate_all ANIM_BOW` |
| 424 | 5184 | 55:1 | 1:46.99 | `bon_odori_lyrics_start_highlight 3, 54` |
| 425 | 5184 | 55:1 | 1:46.99 | `spawn_cue CUE_FORWARD_CLAP` |
| 426 | 5184 | 55:1 | 1:46.99 | `beat_anim` |
| 427 | 5208 | 55:2 | 1:47.48 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 428 | 5208 | 55:2 | 1:47.48 | `spawn_cue CUE_FORWARD_CLAP` |
| 429 | 5208 | 55:2 | 1:47.48 | `beat_anim` |
| 430 | 5232 | 55:3 | 1:47.98 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 431 | 5232 | 55:3 | 1:47.98 | `beat_anim` |
| 432 | 5256 | 55:4 | 1:48.48 | `bon_odori_stop_input_check` |
| 433 | 5256 | 55:4 | 1:48.48 | `bon_odori_lighten_screen 48` |
| 434 | 5256 | 55:4 | 1:48.48 | `beat_anim` |
| 435 | 5280 | 56:1 | 1:48.97 | `bon_odori_lyrics_clear_line 1` |
| 436 | 5280 | 56:1 | 1:48.97 | `bon_odori_lyrics_clear_line 2` |
| 437 | 5280 | 56:1 | 1:48.97 | `bon_odori_lyrics_clear_line 3` |
| 438 | 5280 | 56:1 | 1:48.97 | `beat_anim` |
| 439 | 5304 | 56:2 | 1:49.47 | `beat_anim` |
| 440 | 5328 | 56:3 | 1:49.96 | `beat_anim` |
| 441 | 5352 | 56:4 | 1:50.46 | `beat_anim` |
| 442 | 5376 | 57:1 | 1:50.95 | `beat_anim` |
| 443 | 5400 | 57:2 | 1:51.45 | `beat_anim` |
| 444 | 5424 | 57:3 | 1:51.95 | `bon_odori_animate_all ANIM_BOW` |
| 445 | 5424 | 57:3 | 1:51.95 | `bon_odori_darken_screen 48` |

### 段落起点: tick 5448 / 第 57 小节 / 4  (1:52.44)

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 446 | 5448 | 57:4 | 1:52.44 | `set_marking_criteria 1` |
| 447 | 5460 | 57:4.5 | 1:52.69 | `bon_odori_lyrics_print_left 0, text_bon_odori_ha` |
| 448 | 5460 | 57:4.5 | 1:52.69 | `bon_odori_lyrics_print_center 1, text_bon_odori_ame_ga_agare_ba` |
| 449 | 5472 | 58:1 | 1:52.94 | `bon_odori_lyrics_start_highlight 0, 93` |
| 450 | 5472 | 58:1 | 1:52.94 | `beat_anim` |
| 451 | 5496 | 58:2 | 1:53.43 | `beat_anim` |
| 452 | 5520 | 58:3 | 1:53.93 | `beat_anim` |
| 453 | 5544 | 58:4 | 1:54.43 | `beat_anim` |
| 454 | 5568 | 59:1 | 1:54.92 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 455 | 5568 | 59:1 | 1:54.92 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 456 | 5568 | 59:1 | 1:54.92 | `bon_odori_lyrics_start_highlight 1, 93` |
| 457 | 5568 | 59:1 | 1:54.92 | `beat_anim` |
| 458 | 5592 | 59:2 | 1:55.42 | `beat_anim` |
| 459 | 5616 | 59:3 | 1:55.91 | `beat_anim` |
| 460 | 5640 | 59:4 | 1:56.41 | `beat_anim` |
| 461 | 5664 | 60:1 | 1:56.90 | `bon_odori_start_input_check` |
| 462 | 5664 | 60:1 | 1:56.90 | `bon_odori_lyrics_start_highlight 2, 88` |
| 463 | 5664 | 60:1 | 1:56.90 | `bon_odori_animate_all ANIM_BOW` |
| 464 | 5664 | 60:1 | 1:56.90 | `beat_anim` |
| 465 | 5688 | 60:2 | 1:57.40 | `spawn_cue CUE_SIDE_CLAP` |
| 466 | 5688 | 60:2 | 1:57.40 | `beat_anim` |
| 467 | 5712 | 60:3 | 1:57.90 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 468 | 5712 | 60:3 | 1:57.90 | `spawn_cue CUE_SIDE_CLAP` |
| 469 | 5712 | 60:3 | 1:57.90 | `beat_anim` |
| 470 | 5736 | 60:4 | 1:58.39 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 471 | 5736 | 60:4 | 1:58.39 | `beat_anim` |
| 472 | 5760 | 61:1 | 1:58.89 | `bon_odori_lyrics_clear_line 0` |
| 473 | 5760 | 61:1 | 1:58.89 | `bon_odori_lyrics_clear_line 1` |
| 474 | 5760 | 61:1 | 1:58.89 | `bon_odori_lyrics_start_highlight 3, 54` |
| 475 | 5760 | 61:1 | 1:58.89 | `spawn_cue CUE_FORWARD_CLAP` |
| 476 | 5760 | 61:1 | 1:58.89 | `beat_anim` |
| 477 | 5784 | 61:2 | 1:59.38 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 478 | 5784 | 61:2 | 1:59.38 | `spawn_cue CUE_FORWARD_CLAP` |
| 479 | 5784 | 61:2 | 1:59.38 | `beat_anim` |
| 480 | 5808 | 61:3 | 1:59.88 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 481 | 5808 | 61:3 | 1:59.88 | `beat_anim` |
| 482 | 5832 | 61:4 | 2:00.38 | `bon_odori_stop_input_check` |
| 483 | 5832 | 61:4 | 2:00.38 | `bon_odori_lyrics_print_left 0, text_bon_odori_haa` |
| 484 | 5832 | 61:4 | 2:00.38 | `bon_odori_lyrics_print_center 1, text_bon_odori_yagura_ni_agaru` |
| 485 | 5832 | 61:4 | 2:00.38 | `beat_anim` |
| 486 | 5856 | 62:1 | 2:00.87 | `bon_odori_lyrics_clear_line 2` |
| 487 | 5856 | 62:1 | 2:00.87 | `bon_odori_lyrics_clear_line 3` |
| 488 | 5856 | 62:1 | 2:00.87 | `bon_odori_lyrics_start_highlight 0, 93` |
| 489 | 5856 | 62:1 | 2:00.87 | `beat_anim` |
| 490 | 5880 | 62:2 | 2:01.37 | `beat_anim` |
| 491 | 5904 | 62:3 | 2:01.86 | `beat_anim` |
| 492 | 5928 | 62:4 | 2:02.36 | `beat_anim` |
| 493 | 5952 | 63:1 | 2:02.86 | `bon_odori_lyrics_print_center 2, text_bon_odori_don_don_pan_pan` |
| 494 | 5952 | 63:1 | 2:02.86 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 495 | 5952 | 63:1 | 2:02.86 | `bon_odori_lyrics_start_highlight 1, 93` |
| 496 | 5952 | 63:1 | 2:02.86 | `beat_anim` |
| 497 | 5976 | 63:2 | 2:03.35 | `beat_anim` |
| 498 | 6000 | 63:3 | 2:03.85 | `beat_anim` |
| 499 | 6024 | 63:4 | 2:04.34 | `beat_anim` |
| 500 | 6048 | 64:1 | 2:04.84 | `bon_odori_start_input_check` |
| 501 | 6048 | 64:1 | 2:04.84 | `bon_odori_lyrics_start_highlight 2, 88` |
| 502 | 6048 | 64:1 | 2:04.84 | `bon_odori_animate_all ANIM_BOW` |
| 503 | 6048 | 64:1 | 2:04.84 | `beat_anim` |
| 504 | 6072 | 64:2 | 2:05.33 | `spawn_cue CUE_SIDE_CLAP` |
| 505 | 6072 | 64:2 | 2:05.33 | `beat_anim` |
| 506 | 6096 | 64:3 | 2:05.83 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 507 | 6096 | 64:3 | 2:05.83 | `spawn_cue CUE_SIDE_CLAP` |
| 508 | 6096 | 64:3 | 2:05.83 | `beat_anim` |
| 509 | 6120 | 64:4 | 2:06.33 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 510 | 6120 | 64:4 | 2:06.33 | `beat_anim` |
| 511 | 6144 | 65:1 | 2:06.82 | `bon_odori_lyrics_clear_line 0` |
| 512 | 6144 | 65:1 | 2:06.82 | `bon_odori_lyrics_clear_line 1` |
| 513 | 6144 | 65:1 | 2:06.82 | `bon_odori_lyrics_start_highlight 3, 54` |
| 514 | 6144 | 65:1 | 2:06.82 | `spawn_cue CUE_FORWARD_CLAP` |
| 515 | 6144 | 65:1 | 2:06.82 | `beat_anim` |
| 516 | 6168 | 65:2 | 2:07.32 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 517 | 6168 | 65:2 | 2:07.32 | `spawn_cue CUE_FORWARD_CLAP` |
| 518 | 6168 | 65:2 | 2:07.32 | `beat_anim` |
| 519 | 6192 | 65:3 | 2:07.81 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 520 | 6192 | 65:3 | 2:07.81 | `bon_odori_lyrics_print_left 1, text_bon_odori_hora_matsuri_da_wasshoi` |
| 521 | 6192 | 65:3 | 2:07.81 | `beat_anim` |
| 522 | 6216 | 65:4 | 2:08.31 | `bon_odori_stop_input_check` |
| 523 | 6216 | 65:4 | 2:08.31 | `bon_odori_lyrics_start_highlight 1, 117` |
| 524 | 6216 | 65:4 | 2:08.31 | `beat_anim` |
| 525 | 6240 | 66:1 | 2:08.81 | `bon_odori_lyrics_clear_line 2` |
| 526 | 6240 | 66:1 | 2:08.81 | `bon_odori_lyrics_clear_line 3` |
| 527 | 6240 | 66:1 | 2:08.81 | `beat_anim` |
| 528 | 6264 | 66:2 | 2:09.30 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_panpa_dondo_panpa` |
| 529 | 6264 | 66:2 | 2:09.30 | `beat_anim` |
| 530 | 6288 | 66:3 | 2:09.80 | `beat_anim` |
| 531 | 6312 | 66:4 | 2:10.29 | `beat_anim` |
| 532 | 6336 | 67:1 | 2:10.79 | `bon_odori_start_input_check` |
| 533 | 6336 | 67:1 | 2:10.79 | `bon_odori_animate_all ANIM_BOW` |
| 534 | 6336 | 67:1 | 2:10.79 | `bon_odori_lyrics_start_highlight 3, 86` |
| 535 | 6336 | 67:1 | 2:10.79 | `spawn_cue CUE_SIDE_CLAP` |
| 536 | 6336 | 67:1 | 2:10.79 | `beat_anim` |
| 537 | 6352 | 67:1.667 | 2:11.12 | `spawn_cue CUE_SIDE_CLAP` |
| 538 | 6360 | 67:2 | 2:11.28 | `bon_odori_lyrics_clear_line 1` |
| 539 | 6360 | 67:2 | 2:11.28 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 540 | 6360 | 67:2 | 2:11.28 | `beat_anim` |
| 541 | 6376 | 67:2.667 | 2:11.62 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 542 | 6384 | 67:3 | 2:11.78 | `spawn_cue CUE_SIDE_CLAP` |
| 543 | 6384 | 67:3 | 2:11.78 | `beat_anim` |
| 544 | 6400 | 67:3.667 | 2:12.11 | `spawn_cue CUE_SIDE_CLAP` |
| 545 | 6408 | 67:4 | 2:12.28 | `bon_odori_lyrics_print_left 1, text_bon_odori_korezo` |
| 546 | 6408 | 67:4 | 2:12.28 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 547 | 6408 | 67:4 | 2:12.28 | `beat_anim` |
| 548 | 6424 | 67:4.667 | 2:12.61 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 549 | 6428 | 67:4.833 | 2:12.69 | `bon_odori_lyrics_clear_line 2` |
| 550 | 6428 | 67:4.833 | 2:12.69 | `bon_odori_lyrics_clear_line 3` |

### 段落起点: tick 6432 / 第 68 小节 / 1  (2:12.77)

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 551 | 6432 | 68:1 | 2:12.77 | `set_marking_criteria 2` |
| 552 | 6432 | 68:1 | 2:12.77 | `bon_odori_lyrics_print_right 3, text_bon_odori_meido_in_japan` |
| 553 | 6432 | 68:1 | 2:12.77 | `bon_odori_lyrics_start_highlight 1, 45` |
| 554 | 6432 | 68:1 | 2:12.77 | `beat_anim` |
| 555 | 6480 | 68:3 | 2:13.76 | `bon_odori_lyrics_start_highlight 3, 112` |
| 556 | 6480 | 68:3 | 2:13.76 | `beat_anim` |
| 557 | 6528 | 69:1 | 2:14.76 | `beat_anim` |
| 558 | 6552 | 69:2 | 2:15.25 | `spawn_cue CUE_FORWARD_CLAP` |
| 559 | 6576 | 69:3 | 2:15.75 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 560 | 6576 | 69:3 | 2:15.75 | `bon_odori_set_screen_light` |
| 561 | 6576 | 69:3 | 2:15.75 | `bon_odori_darken_screen 48` |
| 562 | 6576 | 69:3 | 2:15.75 | `beat_anim` |
| 563 | 6592 | 69:3.667 | 2:16.08 | `bon_odori_lyrics_set_y_offset 0` |
| 564 | 6592 | 69:3.667 | 2:16.08 | `bon_odori_lyrics_clear_line 0` |
| 565 | 6592 | 69:3.667 | 2:16.08 | `bon_odori_lyrics_clear_line 1` |
| 566 | 6592 | 69:3.667 | 2:16.08 | `bon_odori_lyrics_clear_line 2` |
| 567 | 6592 | 69:3.667 | 2:16.08 | `bon_odori_lyrics_clear_line 3` |
| 568 | 6600 | 69:4 | 2:16.24 | `bon_odori_stop_input_check` |

### 段落起点: tick 6600 / 第 69 小节 / 4  (2:16.24)

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 569 | 6600 | 69:4 | 2:16.24 | `set_marking_criteria 1` |
| 570 | 6600 | 69:4 | 2:16.24 | `bon_odori_lyrics_print_left 1, text_bon_odori_sore_hikkuri_kaette` |
| 571 | 6600 | 69:4 | 2:16.24 | `bon_odori_lyrics_start_highlight 1, 117` |
| 572 | 6600 | 69:4 | 2:16.24 | `beat_anim` |
| 573 | 6624 | 70:1 | 2:16.74 | `bon_odori_lyrics_clear_line 3` |
| 574 | 6624 | 70:1 | 2:16.74 | `beat_anim` |
| 575 | 6648 | 70:2 | 2:17.24 | `bon_odori_lyrics_print_right 3, text_bon_odori_dondo_pan_pan` |
| 576 | 6648 | 70:2 | 2:17.24 | `beat_anim` |
| 577 | 6672 | 70:3 | 2:17.73 | `bon_odori_animate_all ANIM_SPIN` |
| 578 | 6672 | 70:3 | 2:17.73 | `beat_anim` |
| 579 | 6696 | 70:4 | 2:18.23 | `beat_anim` |
| 580 | 6720 | 71:1 | 2:18.72 | `bon_odori_start_input_check` |
| 581 | 6720 | 71:1 | 2:18.72 | `bon_odori_animate_all ANIM_BOW` |
| 582 | 6720 | 71:1 | 2:18.72 | `bon_odori_lyrics_start_highlight 3, 54` |
| 583 | 6720 | 71:1 | 2:18.72 | `spawn_cue CUE_FORWARD_CLAP` |
| 584 | 6720 | 71:1 | 2:18.72 | `beat_anim` |
| 585 | 6744 | 71:2 | 2:19.22 | `bon_odori_lyrics_clear_line 1` |
| 586 | 6744 | 71:2 | 2:19.22 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 587 | 6744 | 71:2 | 2:19.22 | `spawn_cue CUE_FORWARD_CLAP` |
| 588 | 6744 | 71:2 | 2:19.22 | `beat_anim` |
| 589 | 6768 | 71:3 | 2:19.71 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 590 | 6768 | 71:3 | 2:19.71 | `beat_anim` |
| 591 | 6792 | 71:4 | 2:20.21 | `bon_odori_stop_input_check` |
| 592 | 6792 | 71:4 | 2:20.21 | `bon_odori_lyrics_print_left 0, text_bon_odori_ha_bon_odori` |
| 593 | 6792 | 71:4 | 2:20.21 | `beat_anim` |
| 594 | 6816 | 72:1 | 2:20.71 | `bon_odori_lyrics_clear_line 3` |
| 595 | 6816 | 72:1 | 2:20.71 | `bon_odori_lyrics_start_highlight 0, 93` |
| 596 | 6816 | 72:1 | 2:20.71 | `bon_odori_animate_all ANIM_BOW` |
| 597 | 6816 | 72:1 | 2:20.71 | `beat_anim` |
| 598 | 6840 | 72:2 | 2:21.20 | `bon_odori_lyrics_print_left 1, text_bon_odori_dondo_panpa` |
| 599 | 6840 | 72:2 | 2:21.20 | `bon_odori_lyrics_print_center 2, text_bon_odori_dondo_panpa` |
| 600 | 6840 | 72:2 | 2:21.20 | `bon_odori_lyrics_print_right 3, text_bon_odori_don_pan_pan` |
| 601 | 6864 | 72:3 | 2:21.70 | `beat_anim` |
| 602 | 6912 | 73:1 | 2:22.69 | `bon_odori_start_input_check` |
| 603 | 6912 | 73:1 | 2:22.69 | `bon_odori_lyrics_start_highlight 1, 43` |
| 604 | 6912 | 73:1 | 2:22.69 | `spawn_cue CUE_SIDE_CLAP` |
| 605 | 6912 | 73:1 | 2:22.69 | `beat_anim` |
| 606 | 6928 | 73:1.667 | 2:23.02 | `spawn_cue CUE_SIDE_CLAP` |
| 607 | 6936 | 73:2 | 2:23.19 | `bon_odori_lyrics_clear_line 0` |
| 608 | 6936 | 73:2 | 2:23.19 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 609 | 6936 | 73:2 | 2:23.19 | `beat_anim` |
| 610 | 6952 | 73:2.667 | 2:23.52 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 611 | 6960 | 73:3 | 2:23.68 | `bon_odori_lyrics_start_highlight 2, 43` |
| 612 | 6960 | 73:3 | 2:23.68 | `spawn_cue CUE_SIDE_CLAP` |
| 613 | 6960 | 73:3 | 2:23.68 | `beat_anim` |
| 614 | 6976 | 73:3.667 | 2:24.01 | `spawn_cue CUE_SIDE_CLAP` |
| 615 | 6984 | 73:4 | 2:24.18 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 616 | 6984 | 73:4 | 2:24.18 | `beat_anim` |
| 617 | 7000 | 73:4.667 | 2:24.51 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 618 | 7008 | 74:1 | 2:24.67 | `bon_odori_animate_all ANIM_BOW` |
| 619 | 7008 | 74:1 | 2:24.67 | `bon_odori_lyrics_start_highlight 3, 54` |
| 620 | 7008 | 74:1 | 2:24.67 | `spawn_cue CUE_FORWARD_CLAP` |
| 621 | 7008 | 74:1 | 2:24.67 | `beat_anim` |
| 622 | 7032 | 74:2 | 2:25.17 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 623 | 7032 | 74:2 | 2:25.17 | `spawn_cue CUE_FORWARD_CLAP` |
| 624 | 7032 | 74:2 | 2:25.17 | `beat_anim` |
| 625 | 7056 | 74:3 | 2:25.67 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 626 | 7056 | 74:3 | 2:25.67 | `beat_anim` |
| 627 | 7080 | 74:4 | 2:26.16 | `bon_odori_stop_input_check` |
| 628 | 7080 | 74:4 | 2:26.16 | `bon_odori_lyrics_clear_line 1` |
| 629 | 7080 | 74:4 | 2:26.16 | `bon_odori_lyrics_clear_line 2` |
| 630 | 7080 | 74:4 | 2:26.16 | `bon_odori_lyrics_clear_line 3` |
| 631 | 7080 | 74:4 | 2:26.16 | `beat_anim` |
| 632 | 7092 | 74:4.5 | 2:26.41 | `bon_odori_lyrics_print_left 1, text_bon_odori_dondo_panpa` |
| 633 | 7092 | 74:4.5 | 2:26.41 | `bon_odori_lyrics_print_center 2, text_bon_odori_dondo_panpa` |
| 634 | 7092 | 74:4.5 | 2:26.41 | `bon_odori_lyrics_print_right 3, text_bon_odori_don_pan_pan` |
| 635 | 7104 | 75:1 | 2:26.66 | `bon_odori_start_input_check` |
| 636 | 7104 | 75:1 | 2:26.66 | `bon_odori_lyrics_start_highlight 1, 43` |
| 637 | 7104 | 75:1 | 2:26.66 | `spawn_cue CUE_SIDE_CLAP` |
| 638 | 7104 | 75:1 | 2:26.66 | `beat_anim` |
| 639 | 7120 | 75:1.667 | 2:26.99 | `spawn_cue CUE_SIDE_CLAP` |
| 640 | 7128 | 75:2 | 2:27.15 | `bon_odori_lyrics_clear_line 0` |
| 641 | 7128 | 75:2 | 2:27.15 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 642 | 7128 | 75:2 | 2:27.15 | `beat_anim` |
| 643 | 7144 | 75:2.667 | 2:27.48 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 644 | 7152 | 75:3 | 2:27.65 | `bon_odori_lyrics_start_highlight 2, 43` |
| 645 | 7152 | 75:3 | 2:27.65 | `spawn_cue CUE_SIDE_CLAP` |
| 646 | 7152 | 75:3 | 2:27.65 | `beat_anim` |
| 647 | 7168 | 75:3.667 | 2:27.98 | `spawn_cue CUE_SIDE_CLAP` |
| 648 | 7176 | 75:4 | 2:28.14 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 649 | 7176 | 75:4 | 2:28.14 | `beat_anim` |
| 650 | 7192 | 75:4.667 | 2:28.48 | `bon_odori_animate_npc ANIM_CLAP_F` |
| 651 | 7200 | 76:1 | 2:28.64 | `bon_odori_animate_all ANIM_BOW` |
| 652 | 7200 | 76:1 | 2:28.64 | `bon_odori_lyrics_start_highlight 3, 54` |
| 653 | 7200 | 76:1 | 2:28.64 | `spawn_cue CUE_FORWARD_CLAP` |
| 654 | 7200 | 76:1 | 2:28.64 | `beat_anim` |
| 655 | 7224 | 76:2 | 2:29.14 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 656 | 7224 | 76:2 | 2:29.14 | `spawn_cue CUE_FORWARD_CLAP` |
| 657 | 7224 | 76:2 | 2:29.14 | `beat_anim` |
| 658 | 7248 | 76:3 | 2:29.63 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 659 | 7248 | 76:3 | 2:29.63 | `beat_anim` |
| 660 | 7272 | 76:4 | 2:30.13 | `beat_anim` |
| 661 | 7296 | 77:1 | 2:30.62 | `bon_odori_stop_input_check` |

### 段落起点: tick 7296 / 第 77 小节 / 1  (2:30.62)

| # | tick | 小节:拍 | 时间 | 事件 |
|---:|---:|---:|---:|---|
| 662 | 7296 | 77:1 | 2:30.62 | `set_marking_criteria 3` |
| 663 | 7296 | 77:1 | 2:30.62 | `beat_anim` |
| 664 | 7320 | 77:2 | 2:31.12 | `bon_odori_lyrics_clear_line 1` |
| 665 | 7320 | 77:2 | 2:31.12 | `bon_odori_lyrics_clear_line 2` |
| 666 | 7320 | 77:2 | 2:31.12 | `bon_odori_lyrics_clear_line 3` |
| 667 | 7320 | 77:2 | 2:31.12 | `beat_anim` |
| 668 | 7344 | 77:3 | 2:31.62 | `bon_odori_lyrics_print_center 1, text_bon_odori_pan_pan` |
| 669 | 7344 | 77:3 | 2:31.62 | `beat_anim` |
| 670 | 7368 | 77:4 | 2:32.11 | `beat_anim` |
| 671 | 7392 | 78:1 | 2:32.61 | `bon_odori_animate_all ANIM_BOW` |
| 672 | 7392 | 78:1 | 2:32.61 | `beat_anim` |
| 673 | 7416 | 78:2 | 2:33.10 | `spawn_cue CUE_FORWARD_CLAP` |
| 674 | 7416 | 78:2 | 2:33.10 | `beat_anim` |
| 675 | 7440 | 78:3 | 2:33.60 | `bon_odori_lyrics_start_highlight 1, 34` |
| 676 | 7440 | 78:3 | 2:33.60 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 677 | 7440 | 78:3 | 2:33.60 | `spawn_cue CUE_FORWARD_CLAP` |
| 678 | 7440 | 78:3 | 2:33.60 | `beat_anim` |
| 679 | 7464 | 78:4 | 2:34.09 | `bon_odori_animate_npc ANIM_CLAP_S` |
| 680 | 7464 | 78:4 | 2:34.09 | `beat_anim` |
| 681 | 7488 | 79:1 | 2:34.59 | `bon_odori_lighten_screen 24` |
| 682 | 7488 | 79:1 | 2:34.59 | `bon_odori_lyrics_clear_line 1` |
| 683 | 7488 | 79:1 | 2:34.59 | `stop_tracking_perfect_campaign` |
| 684 | 7560 | 79:4 | 2:36.08 | `disable_pause_menu` |
