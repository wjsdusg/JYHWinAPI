#include "GameEngineTileMap.h"
#include "GameEngineRender.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineResources.h"
#include <GameEngineCore/GameEngineRender.h>

GameEngineTileMap::GameEngineTileMap()
{
}

GameEngineTileMap::~GameEngineTileMap()
{
}

void GameEngineTileMap::CreateTileMap(int _X, int _Y, int _Z, int _Order, float4 _TileSize)
{
    float4 ScreenSize = GameEngineWindow::GetScreenSize();

    TileScale = _TileSize;

    TileRenders.resize(_Z);
    FloorImageName.resize(_Z);
    TileIndexSet.resize(_Z);

    X = _X;
    Y = _Y;
    Z = _Z;

    for (size_t z = 0; z < _Z; z++)
    {
        TileRenders[z].resize(_Y);

        for (size_t y = 0; y < _Y; y++)
        {
            TileRenders[z][y].resize(_X);

            for (size_t x = 0; x < _X; x++)
            {
                GameEngineRender* Render = CreateRender();

                float4 TilePos = _TileSize;
                TilePos.x *= x;
                TilePos.y *= y;
                TilePos.x += _TileSize.hx();
                TilePos.y += _TileSize.hy();
                Render->SetPosition(TilePos);
                Render->SetScale(TileScale);
                Render->SetOrder(_Order + _Z);
                Render->Off();
                TileRenders[z][y][x] = Render;
                
            }
        }
    }


}

void GameEngineTileMap::SetFloorSetting(int _ZIndex, const std::string_view& _ImageName)
{
    if (TileRenders.size() <= _ZIndex)
    {
        MsgAssert("타일을 만들고 floor 이상의 세팅을 하려고 했습니다.");
        return;
    }

    GameEngineImage* Image = GameEngineResources::GetInst().ImageFind(_ImageName);

    if (nullptr == Image)
    {
        MsgAssert("존재하지 않는 이미지로 floor를 세팅할수 없습니다.");
    }

    if (false == Image->IsImageCutting())
    {
        MsgAssert("자르지 않은 이미지는 타일맵에 세팅될 수 없습니다.");
    }

    FloorImageName[_ZIndex] = _ImageName;

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    for (size_t y = 0; y < FloorRenders.size(); y++)
    {
        std::vector<GameEngineRender*>& XLineRenders = FloorRenders[y];

        for (size_t x = 0; x < XLineRenders.size(); x++)
        {
            GameEngineRender* Render = XLineRenders[x];
            // Render->On();
            Render->SetImage(_ImageName);
        }
    }

}

void GameEngineTileMap::SetTileFrame(int _ZIndex, float4 _Pos, int _ImageFrame)
{

    float4 Index = GetIndex(_Pos);

    SetTileFrame(_ZIndex, Index.ix(), Index.iy(), _ImageFrame);
}

void GameEngineTileMap::SetTileFrame(int _ZIndex, int _X, int _Y, int _ImageFrame)
{
    IsValidIndex(_ZIndex, static_cast<float>(_Y), static_cast<float>(_X));

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];
    // 캐칭
    GameEngineRender* TileRender = FloorRenders[_Y][_X];

    TileIndex Index;
    Index.X = _X;
    Index.Y = _Y;
    
    TileIndexSet[_ZIndex].insert(Index.Key);

    TileRender->On();
    TileRender->SetFrame(_ImageFrame);

    return;
}

std::vector<TileIndex> GameEngineTileMap::GetAllTileIndex(int _ZIndex)
{
    std::set<__int64>& Index = TileIndexSet[_ZIndex];

    std::vector<TileIndex> NewTest;

    for (__int64 Key : Index)
    {
        TileIndex Index;
        Index.Key = Key;

        NewTest.push_back(Index);
    }

    return NewTest;
}


float4 GameEngineTileMap::ConvertIndexToTilePosition(float4 _Pos)
{
    float4 Index = GetIndex(_Pos);
    return ConvertIndexToTilePosition(Index.ix(), Index.iy());
}

float4 GameEngineTileMap::ConvertIndexToTilePosition(int _X, int _Y)
{
    return float4(_X * TileScale.x + TileScale.hx(), _Y * TileScale.y + TileScale.hy(), 0.0f, 0.0f) + GetPos();
}

int GameEngineTileMap::GetTileFrame(int _ZIndex, float4 _Pos)
{

    float4 Index = GetIndex(_Pos);

    IsValidIndex(_ZIndex, Index.y, Index.x);

    std::vector<std::vector<GameEngineRender*>>& FloorRenders = TileRenders[_ZIndex];

    GameEngineRender* TileRender = FloorRenders[Index.iy()][Index.ix()];

    if (false == TileRender->IsUpdate())
    {
        return -1;
    }

    return TileRender->GetFrame();
}

bool GameEngineTileMap::IsValidIndex(int _Z, float _Y, float _X)
{
    if (0 > _Z)
    {
        // MsgAssert("Z인덱스가 오버했습니다.");
        return false;
    }

    if (0 > _Y)
    {
        // MsgAssert("Y인덱스가 오버했습니다.");
        return false;
    }

    if (0 > _X)
    {
        // MsgAssert("X인덱스가 오버했습니다.");
        return false;
    }


    if (TileRenders.size() <= _Z)
    {
        // MsgAssert("Z인덱스가 오버했습니다.");
        return false;
    }

    if (TileRenders[_Z].size() < _Y)
    {
        // MsgAssert("Y인덱스가 오버했습니다.");
        return false;
    }

    if (TileRenders[_Z][static_cast<int>(_Y)].size() < _X)
    {
        // MsgAssert("X인덱스가 오버했습니다.");
        return false;
    }

    return true;
}

float4 GameEngineTileMap::GetIndex(float4 _Pos)
{
    float4 Index = _Pos-GetPos();
    Index.x /= TileScale.x;
    Index.y /= TileScale.y;

    return Index;
}

GameEngineRender* GameEngineTileMap::GetTile(int _ZIndex, float4 _Pos)
{
    float4 Index = GetIndex(_Pos);

    if (false == IsValidIndex(_ZIndex, Index.y, Index.x))
    {
        return nullptr;
    }

    return TileRenders[_ZIndex][Index.iy()][Index.ix()];
}



GameEngineRender* GameEngineTileMap::GetTile(int _ZIndex, int _X,int _Y)
{
   

    if (false == IsValidIndex(_ZIndex, static_cast<float>(_Y), static_cast<float>(_X)))
    {
        return nullptr;
    }

    return TileRenders[_ZIndex][_Y][_X];
}



void GameEngineTileMap::RemoveTile(int _ZIndex, float4 _Pos)
{
    float4 Index = GetIndex(_Pos);

    if (false == IsValidIndex(_ZIndex, Index.y, Index.x))
    {
        return;
    }

    TileRenders[_ZIndex][Index.iy()][Index.ix()] = nullptr;
}



void GameEngineTileMap::RemoveTile(int _ZIndex, int _X, int _Y)
{
    if (false == IsValidIndex(_ZIndex, static_cast<float>(_Y), static_cast<float>(_X)))
    {
        return;
    }

     TileRenders[_ZIndex][_Y][_X] = nullptr;
}

void GameEngineTileMap::TileIndexChange(int _Zindex, float4 _CurIndex, float4 _TargetIndex) {
    GameEngineRender* NewgameEngineRender = nullptr;
    float4 CurIndex = GetIndex(_CurIndex);
    float4 TargetIndex= GetIndex(_TargetIndex);
    if (0 > CurIndex.x || 0 > CurIndex.y || 0 > TargetIndex.x || 0 > TargetIndex.y)
    {
        return;
    }
    GameEngineRender* TempGameEngineRender = TileRenders[_Zindex][CurIndex.iy()][CurIndex.ix()];
    TileRenders[_Zindex][CurIndex.iy()][CurIndex.ix()] = TileRenders[_Zindex][TargetIndex.iy()][TargetIndex.ix()];
    TileRenders[_Zindex][TargetIndex.iy()][TargetIndex.ix()] = TempGameEngineRender;
}