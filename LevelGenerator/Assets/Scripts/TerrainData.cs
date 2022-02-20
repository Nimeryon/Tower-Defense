using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum TerrainType
{
    Grass,
    Dirt,
    Sand,
    Water
}

public static class TerrainData
{
    public static TerrainType From(string type)
    {
        switch (type)
        {
            case "G": return TerrainType.Grass;
            case "D":  return TerrainType.Dirt;
            case "S": return TerrainType.Sand;
            case "W": return TerrainType.Water;
            default: return TerrainType.Grass;
        }
    }

    public static TerrainType Next<TerrainType>(this TerrainType type) where TerrainType : struct
    {
        TerrainType[] Values = (TerrainType[])Enum.GetValues(type.GetType());
        int index = Array.IndexOf(Values, type) + 1;
        return (Values.Length == index) ? Values[0] : Values[index];
    }

    public static TerrainType Prior<TerrainType>(this TerrainType type) where TerrainType : struct
    {
        TerrainType[] Values = (TerrainType[])Enum.GetValues(type.GetType());
        int index = Array.IndexOf(Values, type) - 1;
        return (index < 0) ? Values[Values.Length - 1] : Values[index];
    }

    public static void SetBackGround<TerrainType>(this TerrainType type) where TerrainType : struct
    {
        switch (type)
        {
            case global::TerrainType.Grass:
                GUI.backgroundColor = Color.green;
                break;
            case global::TerrainType.Dirt:
                GUI.backgroundColor = Color.red;
                break;
            case global::TerrainType.Water:
                GUI.backgroundColor = Color.blue;
                break;
            case global::TerrainType.Sand:
                GUI.backgroundColor = Color.yellow;
                break;
        }
    }
}
