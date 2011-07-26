----------------------------------------------------------------
-- Copyright (c) 2010-2011 Zipline Games, Inc. 
-- All Rights Reserved. 
-- http://getmoai.com
----------------------------------------------------------------

print = MOAILogMgr.log
print ( "util-physfs" )

MOAISim.openWindow ( "test", 320, 480 )

viewport = MOAIViewport.new ()
viewport:setSize ( 320, 480 )
viewport:setScale ( 320, -480 )

layer = MOAILayer2D.new ()
layer:setViewport ( viewport )
MOAISim.pushRenderPass ( layer )

gfxQuad = MOAIGfxQuad2D.new ()
gfxQuad:setTexture ( "cathead.png" )
gfxQuad:setRect ( -64, -64, 64, 64 )
gfxQuad:setUVRect ( 0, 0, 1, 1 )

prop = MOAIProp2D.new ()
prop:setDeck ( gfxQuad )
layer:insertProp ( prop )

----------------------------------------------------------------
print ( "testPhysFS" )
print ( tostring ( MOAIFileSystem.mount ( "archive.zip", "", 1 )))
print ( tostring ( MOAIFileSystem.checkFileExists ( "file.txt" )))

----------------------------------------------------------------
prop:moveRot ( 360, 1.5 )
