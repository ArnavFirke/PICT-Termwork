------------window dimensions---------------
window_width = 1375
window_height = 750
-------------character attributes------------
easy = {}
easy.x = 400
easy.y = 450
easy.width = 200
easy.height = 200

medium = {}
medium.x = 600
medium.y = 450
medium.width = 200
medium.height = 200


hard = {}
hard.x = 800
hard.y = 450
hard.width = 200
hard.height = 200

space = {}
space.x = 400
space.y = 550
space.width = 50
space.height = 50
--space.background =


office = {}
office.x = 450
office.y = 550
office.width = 50
office.height = 50
--office.background =


basement = {}
basement.x = 500
basement.y = 550
basement.width = 50
basement.height = 50
--basement.background =

button_click1 = "line"
button_click2 = "line"
button_click3 = "line"
button_click4 = "line"
button_click5 = "line"
button_click6 = "line"

anim8 = require("anim8/anim8")

Player = {}
Player.x = window_width / 2
Player.y = 500
Player.width = 40
Player.height = 40
Player.health = 150
Player.maxhealth = 200
Player.image = love.graphics.newImage('playerSheet.png')
Player.grid = anim8.newGrid(614, 564, Player.image:getWidth(), Player.image:getHeight())
Player.animations = {}
Player.animations.idle = anim8.newAnimation(Player.grid('1-15', 1), 0.05)
Player.animations.jump = anim8.newAnimation(Player.grid('1-7', 2), 0.05)
Player.animations.run = anim8.newAnimation(Player.grid('1-15', 3), 0.05)
Player.current_animation = Player.animations.idle
Player.direction = 1


SpaceBackground = {}
SpaceBackground.x = 0
SpaceBackground.y = 0
SpaceBackground.speed = 500
SpaceBackground.image = love.graphics.newImage("assets/space_background.jpeg")


setbackground = space
gamemode = easy
t = 2
time = 0
math.randomseed(os.time())
function collision(v, k)
    return v.x < k.x + k.width and
        v.x + v.width > k.x and
        v.y < k.y + k.height and
        v.y + v.height > k.y
end

function setBackground()
    mx, my = love.mouse.getPosition()

    if love.mouse.isDown(1) then
        if easy.y < my and my < easy.y + easy.width then
            if easy.x < mx and mx < easy.x + easy.width then
                gamemode = easy
                button_click1 = "fill"
                state = "play"
                Sound:play("Earthquake", "Earthquake", 0.5, 1, false)
            elseif medium.x < mx and mx < medium.x + medium.width then
                setbackground = office
                button_click2 = "fill"
                t = 1
                state = "play"
                Sound:play("Earthquake", "Earthquake", 0.5, 1, false)
            elseif hard.x < mx and mx < hard.x + hard.width then
                setbackground = "l̥hard"
                button_click3 = "fill"
                t = 0.5
                state = "play"
                Sound:play("Earthquake", "Earthquake", 0.5, 1, false)
            end
        end
    end
    if love.mouse.isDown(1) then

        if space.y < my and my < space.y + space.width then
            if space.x < mx and mx < space.x + space.width then
                setbackground = space
                button_click4 = "fill"
                state = "play"
            elseif office.x < mx and mx < office.x + office.width then
                setbackground = office
                button_click5 = "fill"
                state = "play"
            elseif basement.x < mx and mx < basement.x + basement.width then
                setbackground = basement
                button_click6 = "fill"
                state = "play"
            end
        end
    end
end

all_obstacles = {}
function createObstacles()
    local obstacle = {}
    -----------obstacle deciding----------------
    r = math.random(1, 4)
    if (r == 1) then
        obstacle.width = 90
        obstacle.height = 90
        obstacle.image = space_couch
    elseif (r == 2) then
        obstacle.width = 70
        obstacle.height = 70
        obstacle.image = space_monitor
    elseif (r == 3) then
        obstacle.width = 100
        obstacle.height = 100
        obstacle.image = space_table
    else
        obstacle.width = 50
        obstacle.height = 50
        obstacle.image = space_bomb
    end
    -----------obstacle attributes--------------
    obstacle.x = math.random(0, window_width - 380 - obstacle.width)
    obstacle.y = -obstacle.height
    obstacle.speed = 200
    obstacle.body = world:newRectangleCollider(obstacle.x, obstacle.y, obstacle.width, obstacle.height)
    obstacle.body:setCollisionClass('platform')
    obstacle.body:setType('dynamic')
    return (obstacle)
end

function love.load()
    state = "menu"
    time = 0
    times = 0
    gamemode = easy
    love.window.setMode(window_width, window_height)
    timer = 0
    obstacle_timer = 0
    background_timer = 0
    main_page = love.graphics.newImage("assets/main_page.jpg")
    space_table = love.graphics.newImage("assets/meteorite.png")
    space_couch = love.graphics.newImage("assets/stones.png")
    space_monitor = love.graphics.newImage("assets/ufo.png")
    space_bomb = love.graphics.newImage("assets/bomb.png")
    space_background = love.graphics.newImage("assets/space_background.jpeg")
    --------------Sounds--------------------------------
    Sound = require("sound")
    Sound:init("Background_Music", "Sounds/Background_3.mp3", "stream")
    Sound:init("objects", "Sounds/Metal_Hit.mp3", "static")
    Sound:init("Objects", "Sounds/wooden_hit.mp3", "static")
    Sound:init("Player", "Sounds/Jump.wav", "static")
    Sound:play("Background_Music", "Background", 0.25, 1, true)
    Sound:init("Earthquake", "Sounds/earthquake.mp3", "stream")
    ----------world generation---------------------------
    wf = require 'library/windfield-master/windfield'
    world = wf.newWorld(0, 500, false)
    world:setQueryDebugDrawing(false)
    -----------collision class---------------------------
    world:addCollisionClass('player')
    world:addCollisionClass('objects')
    world:addCollisionClass('platform')
    world:addCollisionClass('exit')
    ----------character generation-----------------------
    player = world:newRectangleCollider(Player.x, Player.y, Player.width, Player.height)
    player:setFixedRotation(true)
    player.speed = 200
    player.grounded = false
    -----------platform generation-----------------------
    platform = world:newRectangleCollider(0, window_height, window_width + 80, 2, { collision_class = 'platform' })
    platform:setType('static')

    left_border = world:newRectangleCollider(0, 0, 2, window_height)
    left_border:setType('static')

    right_border = world:newRectangleCollider(window_width - 2, 0, 2, window_height)
    right_border:setType('static')

    exit_platform = world:newRectangleCollider(window_width - 380, 200, 400, 2, { collision_class = 'exit' })
    exit_platform:setType('static')


end

function love.update(dt)
    Sound:update()
    time = time + dt
    times = times + dt
    if state == "play" then
        if time < 0.6 and times < 8 then
            if time < 0.2 then
                SpaceBackground.x = SpaceBackground.x + (SpaceBackground.speed * dt)
            end
            if 0.2 < time and time < 0.6 then
                SpaceBackground.x = SpaceBackground.x - (SpaceBackground.speed * dt)
            end
        elseif time < 1.2 and times < 8 then
            if time < 0.8 then
                SpaceBackground.x = SpaceBackground.x + (SpaceBackground.speed * dt)
            end
            if 0.8 < time and time < 1.2 then
                SpaceBackground.x = SpaceBackground.x - (SpaceBackground.speed * dt)
                time = 0
            end
        end



        Sound:setVolume("Background", 0.1)
        world:update(dt)
        timer = timer + dt
        obstacle_timer = obstacle_timer + dt

        local x, y = player:getPosition()
        --if player.grounded==false then
        --Player.current_animation=Player.animations.jump

        if love.keyboard.isDown("d") then
            player:setX(x + player.speed * dt)
            Player.direction = 1
            if player.grounded then
                Player.current_animation = Player.animations.run
            else
                Player.current_animation = Player.animations.jump
            end
        elseif love.keyboard.isDown("a") then
            player:setX(x - player.speed * dt)
            Player.direction = -1
            if player.grounded then
                Player.current_animation = Player.animations.run
            else
                Player.current_animation = Player.animations.jump
            end


        else
            Player.current_animation = Player.animations.idle
        end



        if (obstacle_timer > t) then
            table.insert(all_obstacles, createObstacles())
            obstacle_timer = 0
        end
        for k, v in pairs(all_obstacles) do
            v.y = v.y + v.speed * dt
        end
        if (player.body) then
            local collider = world:queryRectangleArea(player:getX() - 19, player:getY() + 15, 28, 20, { 'objects' })
            local collider2 = world:queryRectangleArea(player:getX() - 19, player:getY() + 15, 28, 20, { "platform" })
            local collider3 = world:queryRectangleArea(player:getX() - 19, player:getY() - 30, 28, 5, { 'platform' })
            --local collider4=world:queryRectangleArea(player:getX(),player:getY()-30,28,5,{'exit'})
            if (#collider > 0) then
                player.grounded = true
            else
                player.grounded = false
            end
            if (#collider2 > 0) then
                player.grounded = true
            else
                player.grounded = false
            end
            if (#collider3 > 0) then
                Player.health = Player.health - dt * 20
                if Player.health < 0 then
                    Player.health = 0
                end
            end
            --if(#collider4>0)then

            --state="win"
            --end
        end
        background_timer = background_timer + dt

        if player:getY() < 20 then
            state = "win"
        end

    end

    if state == "menu" then
        Sound:setVolume("Background", 0.25)
        love.graphics.setNewFont(12)
        if love.keyboard.isDown("space") then
            state = "play"
            Sound:play("Earthquake", "Earthquake", 0.5, 1, false)
        end
        setBackground()
    end
    if Player.health == 0 then
        state = "end"
    end
    Player.current_animation:update(dt)
end

------------if state == "play" then
--Sound:play("Earthquake","Earthquake",0.5,1,false)
--end
function love.keypressed(key)
    ----------character jump----------------------------
    if (key == "space" and player.grounded) then
        Sound:play("Player", "player", 0.40, 1, false)
        player:applyLinearImpulse(0, -1200)

    end
    if (state == "end" and key == 'escape') then
        love.event.quit()
    end
    if (state == "win" and key == 'escape') then
        love.event.quit()
    end
end

function love.draw()
    if state == "play" then
        if time < 0.2 and times < 8 then
            local dx = love.math.random(-1, 1)
            love.graphics.translate(dx * 2, 0)
        end
        love.graphics.draw(space_background, SpaceBackground.x - 250, 0, 0, 1.4, 1.15)

        --world:draw()

        love.graphics.setColor(0, 1, 0)
        love.graphics.print("Health", 50, 150, 0, 2, 2)
        love.graphics.rectangle("fill", 50, 180, Player.health, 5)
        love.graphics.setColor(1, 1, 1)
        Player.current_animation:draw(Player.image, Player.direction == 1 and player:getX() - 10 or player:getX() + 10,
            player:getY() - 38, 0, Player.direction * 0.12, 0.12, Player.width, Player.height)
        for k, v in pairs(all_obstacles) do
            love.graphics.draw(v.image, v.body:getX(), v.body:getY(), v.body:getAngle(), v.width / v.image:getWidth(),
                v.height / v.image:getHeight(), v.image:getWidth() / 2, v.image:getHeight() / 2)
        end
    end
    if state == "menu" then

        love.graphics.setColor(1, 1, 1)
        love.graphics.draw(main_page, 0, 0, 0, 1.5, 1.6)
        love.graphics.setColor(1, 0, 0)
        love.graphics.setNewFont(52)
        love.graphics.print("Space Attack - Survive", 450, 200)
        love.graphics.setNewFont(70)
        love.graphics.print("Pick Difficulty", easy.x, easy.y - 100)
        love.graphics.rectangle(button_click1, easy.x, easy.y, easy.width, easy.height)
        love.graphics.setNewFont(50)
        love.graphics.print("easy", easy.x, easy.y)
        love.graphics.rectangle(button_click2, medium.x, medium.y, medium.width, medium.height)
        love.graphics.print("med", medium.x, medium.y)
        love.graphics.rectangle(button_click3, hard.x, hard.y, hard.width, hard.height)
        love.graphics.print("hard", hard.x, hard.y)

        love.graphics.setColor(1, 1, 1)
    end

    if state == "end" then
        love.graphics.setNewFont(100)
        love.graphics.print("GAME OVER", window_width / 2 - 300, window_height / 2 - 80)
        -- love.graphics.print("press space to play again",window_width/2-220,window_height/2+100,0,3,3)
        love.graphics.setNewFont(70)
        love.graphics.print("Press esc to exit", window_width / 2 - 265, window_height / 2 + 200)
    end
    if state == "win" then
        love.graphics.setNewFont(48)
        love.graphics.print("Congratulation on Surviving the Alien Attack", 150, window_height / 2 - 80)
        --love.graphics.print("press space to play again",window_width/2-220,window_height/2+100,0,3,3)
        love.graphics.print("Press esc to exit", window_width / 2 - 200, window_height / 2 + 200)
    end
end
