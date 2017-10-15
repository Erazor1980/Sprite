#include "Level.h"
#include "SpriteEffect.h"
#include <assert.h>
#include <algorithm>

Level::Level( const std::string& filename )
    :
    m_image( filename )
{
    init();
}

Level::~Level()
{
    if( mp_content )
    {
        delete[] mp_content;
        mp_content = nullptr;
    }
}

void Level::init()
{
//#if _DEBUG
//    m_widthInTiles     = 800 / m_tileSize;
//    m_heightInTiles    = 600 / m_tileSize;
//#else
    m_widthInTiles     = m_image.GetWidth() / m_tileSize;
    m_heightInTiles    = m_image.GetHeight() / m_tileSize;
//#endif

    m_width         = m_image.GetWidth();
    m_height        = m_image.GetHeight();
    m_halfWidth     = m_width / 2;
    m_halfHeight    = m_height / 2;

    assert( m_width > 0 && m_height > 0 && m_heightInTiles > 0 && m_widthInTiles > 0 );
    
    if( mp_content )
    {
        delete[] mp_content;
    }
    mp_content = new Tile[ m_widthInTiles * m_heightInTiles ];

#if 0   /* random level */
    for( int i = 0; i < m_width * m_height; ++i )
    {
        if( rand() % 4 )
        {
            mp_content[ i ] = Tile::EMPTY;
        }
        else
        {
            mp_content[ i ] = Tile::OBSTACLE;
        }
    }
#else   /* test level 2 (river & bridge) */
    for( int i = 0; i < m_widthInTiles * m_heightInTiles; ++i )
    {
        mp_content[ i ] = Tile::EMPTY;
    }

    mp_content[ 8 ] = Tile::OBSTACLE;
    mp_content[ 9 ] = Tile::OBSTACLE;
    mp_content[ 10 ] = Tile::OBSTACLE;
    mp_content[ 11 ] = Tile::OBSTACLE;
    mp_content[ 27 ] = Tile::OBSTACLE;
    mp_content[ 28 ] = Tile::OBSTACLE;
    mp_content[ 29 ] = Tile::OBSTACLE;
    mp_content[ 45 ] = Tile::OBSTACLE;
    mp_content[ 46 ] = Tile::OBSTACLE;
    mp_content[ 49 ] = Tile::OBSTACLE;
    mp_content[ 50 ] = Tile::OBSTACLE;
    mp_content[ 66 ] = Tile::OBSTACLE;
    mp_content[ 67 ] = Tile::OBSTACLE;
    mp_content[ 69 ] = Tile::OBSTACLE;
    mp_content[ 70 ] = Tile::OBSTACLE;
    mp_content[ 86 ] = Tile::OBSTACLE;
    mp_content[ 87 ] = Tile::OBSTACLE;
    for( int i = 95; i <= 99; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    for( int i = 110; i <= 119; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    mp_content[ 120 ] = Tile::OBSTACLE;
    mp_content[ 121 ] = Tile::OBSTACLE;
    mp_content[ 140 ] = Tile::OBSTACLE;
    mp_content[ 141 ] = Tile::OBSTACLE;
    for( int i = 128; i <= 134; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    for( int i = 146; i <= 151; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    mp_content[ 164 ] = Tile::OBSTACLE;
    mp_content[ 167 ] = Tile::OBSTACLE;
    mp_content[ 168 ] = Tile::OBSTACLE;
    mp_content[ 169 ] = Tile::OBSTACLE;
    mp_content[ 175 ] = Tile::OBSTACLE;
    mp_content[ 176 ] = Tile::OBSTACLE;
    mp_content[ 177 ] = Tile::OBSTACLE;
    for( int i = 182; i <= 185; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    for( int i = 200; i <= 206; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    for( int i = 220; i <= 224; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    mp_content[ 240 ] = Tile::OBSTACLE;
    mp_content[ 241 ] = Tile::OBSTACLE;
    mp_content[ 242 ] = Tile::OBSTACLE;
    mp_content[ 260 ] = Tile::OBSTACLE;
    mp_content[ 192 ] = Tile::OBSTACLE;
    mp_content[ 193 ] = Tile::OBSTACLE;
    mp_content[ 212 ] = Tile::OBSTACLE;
    mp_content[ 213 ] = Tile::OBSTACLE;
    mp_content[ 215 ] = Tile::OBSTACLE;
    mp_content[ 216 ] = Tile::OBSTACLE;
    mp_content[ 217 ] = Tile::OBSTACLE;
    for( int i = 235; i <= 238; ++i )
    {
        mp_content[ i ] = Tile::OBSTACLE;
    }
    mp_content[ 257 ] = Tile::OBSTACLE;
    mp_content[ 258 ] = Tile::OBSTACLE;
    mp_content[ 245 ] = Tile::OBSTACLE;
    mp_content[ 246 ] = Tile::OBSTACLE;
    mp_content[ 265 ] = Tile::OBSTACLE;
    mp_content[ 267 ] = Tile::OBSTACLE;
    mp_content[ 268 ] = Tile::OBSTACLE;
    mp_content[ 284 ] = Tile::OBSTACLE;
    mp_content[ 285 ] = Tile::OBSTACLE;
    mp_content[ 287 ] = Tile::OBSTACLE;
    mp_content[ 288 ] = Tile::OBSTACLE;
#endif

    m_bInitialized = true;
}

Vec2 Level::getTileCenter( const int tileIdx ) const
{
    const int xTile = tileIdx % m_widthInTiles;
    const int yTile = tileIdx / m_widthInTiles;

    const float x = xTile * m_tileSize + m_tileSize / 2.0f - 1;
    const float y = yTile * m_tileSize + m_tileSize / 2.0f - 1;

    return Vec2( x, y );
}

void Level::draw( Graphics& gfx, const Vei2& camera, const bool drawGrid ) const
{
    /* calculate RectI of the current visible map snippet */
    const int xStart = std::max( camera.x - Graphics::halfScreenWidth, 0 );
    const int yStart = std::max( camera.y - Graphics::halfScreenHeight, 0 );
    const int xEnd = std::min( m_width, camera.x + Graphics::halfScreenWidth );
    const int yEnd = std::min( m_height, camera.y + Graphics::halfScreenHeight );

    RectI snippet = RectI( xStart, xEnd, yStart, yEnd );

    //gfx.DrawSprite( 0, 0, m_image, SpriteEffect::Copy{} );
    gfx.DrawSprite( 0, 0, snippet, m_image, SpriteEffect::Copy{} );

    if( drawGrid )
    {
        drawTileGrid( gfx );
    }
}

void Level::drawTileGrid( Graphics& gfx ) const
{
    assert( m_height > 0 && m_width > 0 && m_tileSize > 0 );

    for( int x = 0; x < m_widthInTiles; ++x )
    {
        for( int y = 0; y < m_heightInTiles; ++y )
        {
            RectI tile( { x * m_tileSize, y * m_tileSize }, { ( x + 1 ) * m_tileSize - 1, ( y + 1 ) * m_tileSize - 1 } );

            if( Tile::EMPTY == mp_content[ y * m_widthInTiles + x ] )
            {
                gfx.DrawRectBorder( tile, 1, Colors::Green );
            }
            else
            {
                gfx.DrawRectBorder( tile, 1, Colors::Red );
            }
        }
    }
}

void Level::drawPath( Graphics& gfx, std::vector< int > vPath, const int currIdx, const int startIdx, const int targetIdx ) const
{
    /* draw path */
    for( int i = currIdx; i < vPath.size(); ++i )
    {
        const int x = vPath[ i ] % m_widthInTiles;
        const int y = vPath[ i ] / m_widthInTiles;

        RectI tile( { x * m_tileSize, y * m_tileSize }, { ( x + 1 ) * m_tileSize - 1, ( y + 1 ) * m_tileSize - 1 } );

        gfx.DrawCircle( tile.GetCenter().x, tile.GetCenter().y, 4, Colors::White );
    }

    /* draw start and target */
    if( startIdx >= 0 && targetIdx >= 0 )
    {
        const int xS = startIdx % m_widthInTiles;
        const int yS = startIdx / m_widthInTiles;
        RectI start( { xS * m_tileSize, yS * m_tileSize }, { ( xS + 1 ) * m_tileSize - 1, ( yS + 1 ) * m_tileSize - 1 } );
        gfx.DrawRectBorder( start, 2, Colors::Red );

        const int xT = targetIdx % m_widthInTiles;
        const int yT = targetIdx / m_widthInTiles;
        RectI end( { xT * m_tileSize, yT * m_tileSize }, { ( xT + 1 ) * m_tileSize - 1, ( yT + 1 ) * m_tileSize - 1 } );
        gfx.DrawRectBorder( end, 2, Colors::Blue );
    }
}
