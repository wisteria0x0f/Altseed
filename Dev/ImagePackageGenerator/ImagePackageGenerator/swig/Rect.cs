//------------------------------------------------------------------------------
// <auto-generated />
//
// This file was automatically generated by SWIG (http://www.swig.org).
// Version 3.0.6
//
// Do not make changes to this file unless you know what you are doing--modify
// the SWIG interface file instead.
//------------------------------------------------------------------------------

namespace ImagePackageGenerator.swig {

unsafe partial class Rect : global::System.IDisposable {
  private global::System.Runtime.InteropServices.HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal Rect(global::System.IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new global::System.Runtime.InteropServices.HandleRef(this, cPtr);
  }

  internal static global::System.Runtime.InteropServices.HandleRef getCPtr(Rect obj) {
    return (obj == null) ? new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero) : obj.swigCPtr;
  }

  ~Rect() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if (swigCPtr.Handle != global::System.IntPtr.Zero) {
        if (swigCMemOwn) {
          swigCMemOwn = false;
          PSDParserPINVOKE.delete_Rect(swigCPtr);
        }
        swigCPtr = new global::System.Runtime.InteropServices.HandleRef(null, global::System.IntPtr.Zero);
      }
      global::System.GC.SuppressFinalize(this);
    }
  }

  public int Top {
    set {
      PSDParserPINVOKE.Rect_Top_set(swigCPtr, value);
    } 
    get {
      int ret = PSDParserPINVOKE.Rect_Top_get(swigCPtr);
      return ret;
    } 
  }

  public int Left {
    set {
      PSDParserPINVOKE.Rect_Left_set(swigCPtr, value);
    } 
    get {
      int ret = PSDParserPINVOKE.Rect_Left_get(swigCPtr);
      return ret;
    } 
  }

  public int Bottom {
    set {
      PSDParserPINVOKE.Rect_Bottom_set(swigCPtr, value);
    } 
    get {
      int ret = PSDParserPINVOKE.Rect_Bottom_get(swigCPtr);
      return ret;
    } 
  }

  public int Right {
    set {
      PSDParserPINVOKE.Rect_Right_set(swigCPtr, value);
    } 
    get {
      int ret = PSDParserPINVOKE.Rect_Right_get(swigCPtr);
      return ret;
    } 
  }

  public Rect() : this(PSDParserPINVOKE.new_Rect(), true) {
  }

}

}
