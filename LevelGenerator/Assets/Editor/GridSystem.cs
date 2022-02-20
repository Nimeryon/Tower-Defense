using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public enum Direction
{
    NORTH,
    SOUTH,
    WEST,
    EAST
}

public class GridSystem : MonoBehaviour
{
    public const int Width = 32;
    public const int Height = 20;

    private TerrainType[,] Values;

    public GridSystem()
    {
        Values = new TerrainType[Width, Height];
    }

    public static GridSystem LoadFromFile(string levelName)
    {
        string levelFilePath = "../Assets/Terrains/" + levelName + ".txt";
        string[] lines = File.ReadAllLines(levelFilePath);

        GridSystem grid = new();

        for (int y = 0; y < Height; y++)
        {
            string[] values = lines[y].Split(",");
            for (int x = 0; x < Width; x++)
            {
                TerrainType value = TerrainData.From(values[x]);
                grid.SetValue(value, x, y);
            }
        }
        
        return grid;
    }

    // Getters
    public TerrainType GetValue(int x, int y)
    {
        if (!IsBounded(x, y)) return TerrainType.Grass;
        return Values[x, y];
    }

    // Setters
    public void SetValue(TerrainType value, int x, int y)
    {
        if (!IsBounded(x, y)) return;
        Values[x, y] = value;
    }
    public void SetNextValue(int x, int y)
    {
        if (!IsBounded(x, y)) return;
        SetValue(GetValue(x, y).Next(), x, y);
    }
    public void SetPriorValue(int x, int y)
    {
        if (!IsBounded(x, y)) return;
        SetValue(GetValue(x, y).Prior(), x, y);
    }
    public void SetRowNext(int y)
    {
        if (!IsBounded(0, y)) return;
        for (int x = 0; x < Width; x++)
        {
            SetNextValue(x, y);
        }
    }
    public void SetRowPrior(int y)
    {
        if (!IsBounded(0, y)) return;
        for (int x = 0; x < Width; x++)
        {
            SetPriorValue(x, y);
        }
    }
    public void SetColNext(int x)
    {
        if (!IsBounded(x, 0)) return;
        for (int y = 0; y < Height; y++)
        {
            SetNextValue(x, y);
        }
    }
    public void SetColPrior(int x)
    {
        if (!IsBounded(x, 0)) return;
        for (int y = 0; y < Height; y++)
        {
            SetPriorValue(x, y);
        }
    }

    // Utilities
    public void MoveLine(Direction direction)
    {
        TerrainType[,] newValues;
        switch (direction)
        {
            case Direction.NORTH:
                newValues = new TerrainType[Width, Height];
                for (int y = 1; y < Height; y++)
                {
                    for (int x = 0; x < Width; x++)
                    {
                        newValues[x, y - 1] = GetValue(x, y);
                    }
                }

                for (int x = 0; x < Width; x++)
                {
                    newValues[x, Height - 1] = GetValue(x, 0);
                }
                Values = newValues;
                break;

            case Direction.SOUTH:
                newValues = new TerrainType[Width, Height];
                for (int y = 0; y < Height - 1; y++)
                {
                    for (int x = 0; x < Width; x++)
                    {
                        newValues[x, y] = GetValue(x, y + 1);
                    }
                }

                for (int x = 0; x < Width; x++)
                {
                    newValues[x, 0] = GetValue(x, Height - 1);
                }
                Values = newValues;
                break;

            case Direction.WEST:
                newValues = new TerrainType[Width, Height];
                for (int y = 0; y < Height; y++)
                {
                    for (int x = 1; x < Width; x++)
                    {
                        newValues[x - 1, y] = GetValue(x, y);
                    }
                }

                for (int y = 0; y < Height; y++)
                {
                    newValues[Width - 1, y] = GetValue(Width, y);
                }
                
                Values = newValues;
                break;

            case Direction.EAST:
                newValues = new TerrainType[Width, Height]; for (int y = 0; y < Height; y++)
                {
                    for (int x = 0; x < Width - 1; x++)
                    {
                        newValues[x + 1, y] = GetValue(x, y);
                    }
                }

                for (int y = 0; y < Height; y++)
                {
                    newValues[0, y] = GetValue(Width - 1, y);
                }
                Values = newValues;
                break;
        }
    }
    public void Clear()
    {
        for (int y = 0; y < Height; y++)
        {
            for (int x = 0; x < Width; x++)
            {
                SetValue(TerrainType.Grass, x, y);
            }
        }
    }
    public async void SaveToFile(string levelName, Vector2Int startPos, Direction startDirection, Vector2Int endPos, List<EndOfIntersection> endOfIntersections)
    {
        if (!Directory.Exists("../Assets/Terrains")) Directory.CreateDirectory("../Assets/Terrains");
        string levelFilePath = "../Assets/Terrains/" + levelName + ".txt";
        List<string> lines = new List<string>();
        for (int y = 0; y < Height; y++)
        {
            string line = "";
            for (int x = 0; x < Width; x++)
                line += GetValue(x, y).ToString()[0];
            lines.Add(line);
        }
        lines.Add(startPos.x + "," + startPos.y + "," + startDirection);
        lines.Add(endOfIntersections.Count.ToString());
        foreach (var endOfIntersection in endOfIntersections)
            lines.Add(endOfIntersection.position.x + "," + endOfIntersection.position.y + "," + endOfIntersection.endDirection);
        lines.Add(endPos.x + "," + endPos.y);

        await File.WriteAllLinesAsync(levelFilePath, lines);
        Debug.Log("Level " + levelName + " created!");
    }

    private bool IsBounded(int x, int y)
    {
        return x >= 0 && y >= 0 && x < Width && y < Height;
    }
}
