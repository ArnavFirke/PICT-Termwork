windowwidth=1375
windowheight=750

function player_phy(dt)
    
    wf = require 'library/windfield-master/windfield'
    world = wf.newWorld(0,500,false)

    world:addCollisionClass('player')
    world:addCollisionClass('objects')

    player = world:newRectangleCollider(0,360,30,30)
    player:setFixedRotation(true)
    player.speed=200

    platform = world:newRectangleCollider(0,windowheight,windowwidth+80,2,{collision_class='player'})
    platform:setType('static')
    
    
    objects = world:newRectangleCollider(720,360,60,30,{collision_class='objects'})
    objects:setType('static')
   
end

function player_movement()
    
   
    world:update(dt)
    timer=timer+dt

    local x,y = player:getPosition()
    if love.keyboard.isDown("d")then
        player:setX(x+player.speed*dt) 
    end

    if love.keyboard.isDown("a")then
        player:setX(x-player.speed*dt) 
    end

    if timer>3 then
        objects:setType('dynamic')
    end


end





