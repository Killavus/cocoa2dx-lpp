-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

function myadd(x, y)
    return x + y
end

local function main()
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    
    local cclog = function(...)
        print(string.format(...))
    end
    
    cclog("result is " .. myadd(3, 5))
    local sceneGame = CCDirector:sharedDirector():getRunningScene()
    local visibleSize = CCDirector:sharedDirector():getVisibleSize()
    cclog(visibleSize.height)
    local bg = CCSprite:create("HelloWorld.png")
    bg:setPosition(visibleSize.width/2,visibleSize.height/2)
    sceneGame:addChild(bg,-1)
end

xpcall(main, __G__TRACKBACK__)