using System.Collections;
using System.Collections.Generic;
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
    private string levelName = "";

    private Vector2Int startPos = Vector2Int.zero;
    private Direction startDirection = Direction.SOUTH;
    private Vector2Int endPos = new (GridSystem.Width, GridSystem.Height);
    private List<EndOfIntersection> endOfIntersections = new ();

    private GUIStyle borderStart;
    private GUIStyle borderEnd;

    private Vector2 endOfIntersectionsScroll;

    [MenuItem("Game/Level")]
    public static void Init()
    {
        GetWindow<LevelWindow>("Level");
    }

    void OnGUI()
    {
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
    }

    private void ResetBackgroundColor() { GUI.backgroundColor = Color.white; }

    private void Separator()
    {
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
    }

    private void ShowHeader()
    {        
        // Header
        GUILayout.Label("Level Name");
        levelName = GUILayout.TextField(levelName);

        GUILayout.Space(16);

        GUILayout.BeginHorizontal();
        GUILayout.BeginVertical();
        startPos.x = EditorGUILayout.IntSlider("Start position x", startPos.x, 0, GridSystem.Width - 1);
        startPos.y = EditorGUILayout.IntSlider("Start position y", startPos.y, 0, GridSystem.Height - 1);
        startDirection = (Direction)EditorGUILayout.EnumPopup("Start direction", startDirection);
        GUILayout.EndVertical();

        GUILayout.BeginVertical();
        endPos.x = EditorGUILayout.IntSlider("End position x", endPos.x, 0, GridSystem.Width - 1);
        endPos.y = EditorGUILayout.IntSlider("End position y", endPos.y, 0, GridSystem.Height - 1);
        GUILayout.EndVertical();
        GUILayout.EndHorizontal();

        GUILayout.Space(16);

        // Buttons
        GUILayout.BeginHorizontal();
        if (GUILayout.Button("Reset Values")) { grid.Clear(); }
        if (GUILayout.Button("Save Level")) { grid.SaveToFile(levelName, startPos, startDirection, endPos, endOfIntersections); }
        GUILayout.EndHorizontal();
    }

    private void ShowEndOfIntersections()
    {
        GUILayout.BeginHorizontal();
        GUILayout.Label("End of intersections");
        if (GUILayout.Button("+", GUILayout.Width(64))) { endOfIntersections.Add(new EndOfIntersection()); }
        if (GUILayout.Button("-", GUILayout.Width(64))) { endOfIntersections.RemoveAt(endOfIntersections.Count - 1); }
        GUILayout.EndHorizontal();

        Separator();

        // End of intersections
        for (int i = 0; i < endOfIntersections.Count; ++i)
        {
            if (i != 0) Separator();
            GUILayout.BeginVertical();
            endOfIntersections[i].position.x = EditorGUILayout.IntSlider("Intersection x", endOfIntersections[i].position.x, 0, GridSystem.Width - 1);
            endOfIntersections[i].position.y = EditorGUILayout.IntSlider("Intersection y", endOfIntersections[i].position.y, 0, GridSystem.Height - 1);
            endOfIntersections[i].endDirection = (Direction)EditorGUILayout.EnumPopup("Intersection direction", endOfIntersections[i].endDirection);
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
                if (new Vector2Int(x, y) == startPos) GUI.backgroundColor = Color.magenta;
                if (new Vector2Int(x, y) == endPos) GUI.backgroundColor = Color.cyan;
                if (endOfIntersections.Any(endOfIntersection => endOfIntersection.position == new Vector2Int(x, y))) GUI.backgroundColor = Color.white;
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