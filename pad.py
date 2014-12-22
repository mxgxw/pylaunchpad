# Copyright 2014 - Mario Gomez <mario.gomez_at_teubi.co>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import pygame

def main():
  pygame.init()
  pygame.mixer.init()
  screen = pygame.display.set_mode((640,480))

  # Key mapping for the 4x4 PAD
  btn_map = [
    [pygame.K_1,pygame.K_2,pygame.K_3,pygame.K_4],
    [pygame.K_q,pygame.K_w,pygame.K_e,pygame.K_r],
    [pygame.K_a,pygame.K_s,pygame.K_d,pygame.K_f],
    [pygame.K_z,pygame.K_x,pygame.K_c,pygame.K_v]
    ]
  # Key mapping for loops
  loop_map = [pygame.K_F1,pygame.K_F2,pygame.K_F3,pygame.K_F4]
  
  btn_state = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
  sounds = [[],[],[],[]]
  loops = []
  btn_loop_state = [0,0,0,0]
  snd_loop = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
  snd_fade = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
  
  # Load sammples
  for i in range(4):
    for j in range(4):
      sounds[j].append(pygame.mixer.Sound('./samples/'+str(j+1)+'-'+str(i+1)+'.ogg'))
  # Load loops
  for i in range(4):
    loops.append(pygame.mixer.Sound('./loops/'+str(i+1)+'.ogg'))
    
  screen.fill((0,0,0))

  for i in range(4):
    for j in range(4):
      pygame.draw.rect(screen,(255,255,255),(120+(j*102),40+(i*102),98,98))
  
  for i in range(4):
    pygame.draw.rect(screen,(255,255,255),(528,40+(i*102),48,98))

  while True:
    for event in pygame.event.get():
      if event.type == pygame.QUIT:
        return
      if event.type == pygame.KEYDOWN:
	for i in range(4):
	  if event.key == loop_map[i]:
	    if btn_loop_state[i] == 0:
	      loops[i].play(-1)
	      pygame.draw.rect(screen,(0,255,0),(528,40+(i*102),48,98))
	      btn_loop_state[i] = 1
	    else:
	      loops[i].stop()
	      pygame.draw.rect(screen,(255,255,255),(528,40+(i*102),48,98))
	      btn_loop_state[i] = 0
	  for j in range(4):
	    if event.key == btn_map[i][j]:
	      if btn_state[i][j] == 0:
		sounds[i][j].play(snd_loop[i][j])
		pygame.draw.rect(screen,(0,255,0),(120+(j*102),40+(i*102),98,98))
		btn_state[i][j] = 1
      if event.type == pygame.KEYUP:
	for i in range(4):
	  for j in range(4):
	    if event.key == btn_map[i][j]:
	      if btn_state[i][j] == 1:
		sounds[i][j].stop()
		pygame.draw.rect(screen,(255,255,255),(120+(j*102),40+(i*102),98,98))
		btn_state[i][j] = 0
		
    pygame.display.flip()

main()
