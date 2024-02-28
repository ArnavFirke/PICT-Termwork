anim8 = require 'anim8/anim8'

player={}
player.x=200
player.y=200
player.width=20
player.height=20
player.image=love.graphics.newImage('playerSheet.png')
player.grid=anim8.newGrid(614,564,player.image:getWidth(),player.image:getHeight())
player.animations={}
player.animations.idle=anim8.newAnimation(player.grid('1-15',1),0.05)
player.animations.jump=anim8.newAnimation(player.grid('1-7',2),0.05)
player.animations.run=anim8.newAnimation(player.grid('1-15',3),0.05)
player.current_animation=player.animations.idle
player.direction=1
function love.update(dt)
  if(love.keyboard.isDown('d'))then
    player.direction=1
    player.current_animation=player.animations.run
  elseif(love.keyboard.isDown('a'))then
    player.direction=-1
    player.current_animation=player.animations.run
  elseif(love.keyboard.isDown('space'))then
    player.current_animation=player.animations.jump
  else
    player.current_animation=player.animations.idle
  end
  player.current_animation:update(dt)
end

function love.draw()
  player.current_animation:draw(player.image,player.direction==1 and player.x-60 or player.x+60,player.y-30,0,player.direction*0.5,0.5,player.width,player.height)
end
