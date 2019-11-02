using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
using System;


public class DllTest : MonoBehaviour
{
    [DllImport("dllhook", ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
    public static extern IntPtr Create();

    [DllImport("dllhook", ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
    public static extern void Init(IntPtr ocu, int width, int height, int channels);

    [DllImport("dllhook", ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
    public static extern void BlurCuda(IntPtr ocu, IntPtr input, IntPtr output);

    WebCamTexture webcamTexture;
    Texture2D webcamFrame;
    Color32[] pixel;
    GCHandle pixel_handle;
    IntPtr pixel_pointer;
    int width;
    int height;
    int channels;

    // [O]penCV, [C]uda, for [U]nity = OCU
    IntPtr ocu;
    Texture2D outputFrame;
    Color32[] output_pixel;
    GCHandle output_pixel_handle;
    IntPtr output_pixel_pointer;

    public GameObject outputObject;

    // Start is called before the first frame update
    void Start()
    {
        // Input from webcam
        webcamTexture = new WebCamTexture();
        Renderer renderer = GetComponent<Renderer>();
        renderer.material.mainTexture = webcamTexture;
        webcamTexture.Play();
        width = webcamTexture.width;
        height = webcamTexture.height;

        // Create texture to pass to DLL
        webcamFrame = new Texture2D(width, height, TextureFormat.ARGB32, false);

        // Set output maintexture to output frame
        outputFrame = new Texture2D(width, height, TextureFormat.ARGB32, false);
        outputObject.GetComponent<Renderer>().material.mainTexture = outputFrame;

        // Initialize CUDA containers
        ocu = Create();
        Init(ocu, width, height, 4);
    }

    // Update is called once per frame
    void Update()
    {
        if (!webcamTexture.isPlaying) return;

        webcamFrame.SetPixels(webcamTexture.GetPixels());
        pixel = webcamFrame.GetPixels32();
        pixel_handle = GCHandle.Alloc(pixel, GCHandleType.Pinned);
        pixel_pointer = pixel_handle.AddrOfPinnedObject();

        output_pixel = outputFrame.GetPixels32();
        output_pixel_handle = GCHandle.Alloc(output_pixel, GCHandleType.Pinned);
        output_pixel_pointer = output_pixel_handle.AddrOfPinnedObject();

        BlurCuda(ocu, pixel_pointer, output_pixel_pointer);

        outputFrame.SetPixels32(output_pixel);
        outputFrame.Apply();
    }
}
