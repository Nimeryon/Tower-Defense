using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using UnityEngine;
using UnityEditor;

public class EndOfIntersection
{
    public Vector2Int position;
    public Direction endDirection;
}

public class LevelWindow : EditorWindow
{
    private GridSystem grid = new();

    private Vector2 globalScroll;
    private Vector2 endOfIntersectionsScroll;

    private int selectedLevelPopup;

    [MenuItem("Game/Level")]
    public static void Init()
    {
        GetWindow<LevelWindow>("Level");
    }

    void OnGUI()
    {
        globalScroll = GUILayout.BeginScrollView(globalScroll, false, true);
        LoadFromFiles();
        Separator();
        ShowHeader();
        Separator();

        GUILayout.BeginHorizontal();

        endOfIntersectionsScroll = GUILayout.BeginScrollView(endOfIntersectionsScroll, false, true);
        GUILayout.BeginVertical();
        ShowEndOfIntersections();
        GUILayout.EndVertical();
        GUILayout.EndScrollView();

        GUILayout.BeginVertical();
        ShowGrid();
        GUILayout.EndVertical();

        GUILayout.EndHorizontal();
        GUILayout.EndScrollView();
    }

    private void ResetBackgroundColor() { GUI.backgroundColor = Color.white; }

    private void Separator()
    {
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
    }

    private void LoadFromFiles()
    {
        GUILayout.BeginHorizontal();

        string[] fileNames = Directory.GetFiles("../Assets/Terrains/");
        for (int i = 0; i < fileNames.Length; ++i)
            fileNames[i] = fileNames[i].Replace("../Assets/Terrains/", "");

        selectedLevelPopup = EditorGUILayout.Popup("Levels", selectedLevelPopup, fileNames);
        if (GUILayout.Button("Load"))
            grid = GridSystem.LoadFromFile(fileNames[selectedLevelPopup]);

        GUILayout.EndHorizontal();
    }

    private void ShowHeader()
    {        
        // Header
        GUILayout.Label("Level Name");
        grid.levelName = GUILayout.TextField(grid.levelName);

        GUILayout.Space(16);

        GUILayout.BeginHorizontal();
        GUILayout.BeginVertical();
        grid.startPos.x = EditorGUILayout.IntSlider("Start position x", grid.startPos.x, 0, GridSystem.Width - 1);
        grid.startPos.y = EditorGUILayout.IntSlider("Start position y", grid.startPos.y, 0, GridSystem.Height - 1);
        grid.startDirection = (Direction)EditorGUILayout.EnumPopup("Start direction", grid.startDirection);
        GUILayout.EndVertical();

        GUILayout.BeginVertical();
        grid.endPos.x = EditorGUILayout.IntSlider("End position x", grid.endPos.x, 0, GridSystem.Width - 1);
        grid.endPos.y = EditorGUILayout.IntSlider("End position y", grid.endPos.y, 0, GridSystem.Height - 1);
        GUILayout.EndVertical();
        GUILayout.EndHorizontal();

        GUILayout.Space(16);

        // Buttons
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("Reset Values")) { grid.Clear(); }
        if (GUILayout.Button("Save Level")) { grid.SaveToFile(); }
        GUILayout.EndHorizontal();
    }

    private void ShowEndOfIntersections()
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label("End of intersections");
        if (GUILayout.Button("+", GUILayout.Width(64))) { grid.endOfIntersections.Add(new EndOfIntersection()); }
        if (GUILayout.Button("-", GUILayout.Width(64))) { grid.endOfIntersections.RemoveAt(grid.endOfIntersections.Count - 1); }
        GUILayout.EndHorizontal();

        Separator();

        // End of intersections
        for (int i = 0; i < grid.endOfIntersections.Count; ++i)
        {
            if (i != 0) Separator();
            GUILayout.BeginVertical();
            grid.endOfIntersections[i].position.x = EditorGUILayout.IntSlider("Intersection x", grid.endOfIntersections[i].position.x, 0, GridSystem.Width - 1);
            grid.endOfIntersections[i].position.y = EditorGUILayout.IntSlider("Intersection y", grid.endOfIntersections[i].position.y, 0, GridSystem.Height - 1);
            grid.endOfIntersections[i].endDirection = (Direction)EditorGUILayout.EnumPopup("Intersection direction", grid.endOfIntersections[i].endDirection);
            GUILayout.EndVertical();
        }
    }

    private void ShowGrid()
    {
        // Editor
        GUILayout.FlexibleSpace();

        // North buttons
        GUILayout.BeginHorizontal();
        GUILayout.FlexibleSpace();
        if (GUILayout.Button("^", GUILayout.Width(24), GUILayout.Height(24))) { grid.MoveLine(Direction.NORTH); }
        GUILayout.FlexibleSpace();
        GUILayout.EndHorizontal();
        GUILayout.Space(8);

        // Full col buttons
        GUILayout.BeginHorizontal();
        GUILayout.FlexibleSpace();
        GUILayout.Box("", GUILayout.Width(24), GUILayout.Height(24));
        for (int x = 0; x < GridSystem.Width; x++)
        {
            if (GUILayout.Button("V", GUILayout.Width(24), GUILayout.Height(24)))
            {
                if (Event.current.button == 1)
                {
                    grid.SetColPrior(x);
                }
                else
                {
                    grid.SetColNext(x);
                }
            }
        }
        GUILayout.FlexibleSpace();
        GUILayout.EndHorizontal();

        // Setup grid buttons
        int halfHeight = (GridSystem.Height / 2) - 1;
        for (int y = 0; y < GridSystem.Height; y++)
        {
            // Button col
            GUILayout.BeginHorizontal();
            GUILayout.FlexibleSpace();

            // West buttons
            if (y == halfHeight)
            {
                if (GUILayout.Button("<", GUILayout.Width(24), GUILayout.Height(24))) { grid.MoveLine(Direction.WEST); }
                GUILayout.Space(8);
            }

            for (int x = 0; x < GridSystem.Width; x++)
            {
                // Full row button
                if (x == 0)
                {
                    ResetBackgroundColor();
                    if (GUILayout.Button("=>", GUILayout.Width(24), GUILayout.Height(24)))
                    {
                        if (Event.current.button == 1)
                        {
                            grid.SetRowPrior(y);
                        }
                        else
                        {
                            grid.SetRowNext(y);
                        }
                    }
                }

                // Single cell button
                grid.GetValue(x, y).SetBackGround();
                if (new Vector2Int(x, y) == grid.startPos) GUI.backgroundColor = Color.magenta;
                if (new Vector2Int(x, y) == grid.endPos) GUI.backgroundColor = Color.cyan;
                if (grid.endOfIntersections.Any(endOfIntersection => endOfIntersection.position == new Vector2Int(x, y))) GUI.backgroundColor = Color.white;
                if (GUILayout.Button(grid.GetValue(x, y).ToString()[0].ToString(), GUILayout.Width(24), GUILayout.Height(24)))
                {
                    if (Event.current.button == 1)
                    {
                        grid.SetPriorValue(x, y);
                    }
                    else
                    {
                        grid.SetNextValue(x, y);
                    }
                }
            }

            // Est buttons
            ResetBackgroundColor();
            if (y == halfHeight)
            {
                GUILayout.Space(8);
                if (GUILayout.Button(">", GUILayout.Width(24), GUILayout.Height(24))) { grid.MoveLine(Direction.EAST); }
            }

            GUILayout.FlexibleSpace();
            GUILayout.EndHorizontal();
        }

        ResetBackgroundColor();

        // South buttons
        GUILayout.Space(8);
        GUILayout.BeginHorizontal();
        GUILayout.FlexibleSpace();
        if (GUILayout.Button("V", GUILayout.Width(24), GUILayout.Height(24))) { grid.MoveLine(Direction.SOUTH); }
        GUILayout.FlexibleSpace();
        GUILayout.EndHorizontal();

        GUILayout.FlexibleSpace();
    }
}