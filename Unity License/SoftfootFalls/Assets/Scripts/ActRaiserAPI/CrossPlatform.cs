using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public abstract class CrossPlatform : MonoBehaviour
{
    public static void Quit()
    {
#if UNITY_EDITOR
        UnityEditor.EditorApplication.isPlaying = false;
#endif
#if UNITY_STANDALONE
        Application.Quit();
#endif
    }
}
