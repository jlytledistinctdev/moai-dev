layer = MOAILayer2D.new ()
MOAISim.pushRenderPass ( layer )

MOAISim.openWindow ( "picking", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, 480 )
layer:setViewport ( viewport )

partition = MOAIPartition.new ()
layer:setPartition ( partition )

texture = MOAITexture.new ()
texture:load ( "cathead.png" )
texture:setRect ( -64, -64, 64, 64 )

--sprites = {}

function addSprite ( x, y, xScl, yScl, name )
	local sprite = MOAISprite2D.new ()
	sprite:setGfxSource ( texture )
	sprite:setPriority ( priority )
	sprite:setLoc ( x, y )
	sprite:setScl ( xScl, yScl )
	sprite.name = name
	--table.insert ( sprites, sprite )
	partition:insertPrim ( sprite )
end

addSprite ( -64, 64, 0.5, 0.5, "sprite1" )
addSprite ( 64, 64, 0.5, 0.5, "sprite2" )
addSprite ( 0, 0, 0.5, 0.5, "sprite3" )
addSprite ( 64, -64, 0.5, 0.5, "sprite4" )
addSprite ( -64, -64, 0.5, 0.5, "sprite5" )

mouseX = 0
mouseY = 0

priority = 1

local function printf ( ... )
	return io.stdout:write ( string.format ( ... ))
end 

MOAIInputMgr.device.pointer:setCallback (
	function ( x, y )
		
		local oldX = mouseX
		local oldY = mouseY
		
		mouseX, mouseY = layer:wndToWorld ( x, y )
		
		if pick then
			pick:addLoc ( mouseX - oldX, mouseY - oldY )
		end
	end
)

MOAIInputMgr.device.mouseLeft:setCallback (
	function ( down )
	
		if down then
			
			pick = partition:primForPoint ( mouseX, mouseY )
			
			if pick then
				print ( pick.name )
				pick:setPriority ( priority )
				priority = priority + 1
				pick:moveScl ( 0.25, 0.25, 0.125, MOAITransition.EASE_IN )
			end
		else
			if pick then
				pick:moveScl ( -0.25, -0.25, 0.125, MOAITransition.EASE_IN )
				pick = nil
			end
		end
	end
)