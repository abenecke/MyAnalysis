// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME objdISUHH2ZPrimeTotTPrime_dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "include/ZPrimeTotTPrimeReconstructionHypothesis.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *ZPrimeTotTPrimeReconstructionHypothesis_Dictionary();
   static void ZPrimeTotTPrimeReconstructionHypothesis_TClassManip(TClass*);
   static void *new_ZPrimeTotTPrimeReconstructionHypothesis(void *p = 0);
   static void *newArray_ZPrimeTotTPrimeReconstructionHypothesis(Long_t size, void *p);
   static void delete_ZPrimeTotTPrimeReconstructionHypothesis(void *p);
   static void deleteArray_ZPrimeTotTPrimeReconstructionHypothesis(void *p);
   static void destruct_ZPrimeTotTPrimeReconstructionHypothesis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ZPrimeTotTPrimeReconstructionHypothesis*)
   {
      ::ZPrimeTotTPrimeReconstructionHypothesis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ZPrimeTotTPrimeReconstructionHypothesis));
      static ::ROOT::TGenericClassInfo 
         instance("ZPrimeTotTPrimeReconstructionHypothesis", "include/ZPrimeTotTPrimeReconstructionHypothesis.h", 9,
                  typeid(::ZPrimeTotTPrimeReconstructionHypothesis), DefineBehavior(ptr, ptr),
                  &ZPrimeTotTPrimeReconstructionHypothesis_Dictionary, isa_proxy, 4,
                  sizeof(::ZPrimeTotTPrimeReconstructionHypothesis) );
      instance.SetNew(&new_ZPrimeTotTPrimeReconstructionHypothesis);
      instance.SetNewArray(&newArray_ZPrimeTotTPrimeReconstructionHypothesis);
      instance.SetDelete(&delete_ZPrimeTotTPrimeReconstructionHypothesis);
      instance.SetDeleteArray(&deleteArray_ZPrimeTotTPrimeReconstructionHypothesis);
      instance.SetDestructor(&destruct_ZPrimeTotTPrimeReconstructionHypothesis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ZPrimeTotTPrimeReconstructionHypothesis*)
   {
      return GenerateInitInstanceLocal((::ZPrimeTotTPrimeReconstructionHypothesis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ZPrimeTotTPrimeReconstructionHypothesis*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ZPrimeTotTPrimeReconstructionHypothesis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ZPrimeTotTPrimeReconstructionHypothesis*)0x0)->GetClass();
      ZPrimeTotTPrimeReconstructionHypothesis_TClassManip(theClass);
   return theClass;
   }

   static void ZPrimeTotTPrimeReconstructionHypothesis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_ZPrimeTotTPrimeReconstructionHypothesis(void *p) {
      return  p ? new(p) ::ZPrimeTotTPrimeReconstructionHypothesis : new ::ZPrimeTotTPrimeReconstructionHypothesis;
   }
   static void *newArray_ZPrimeTotTPrimeReconstructionHypothesis(Long_t nElements, void *p) {
      return p ? new(p) ::ZPrimeTotTPrimeReconstructionHypothesis[nElements] : new ::ZPrimeTotTPrimeReconstructionHypothesis[nElements];
   }
   // Wrapper around operator delete
   static void delete_ZPrimeTotTPrimeReconstructionHypothesis(void *p) {
      delete ((::ZPrimeTotTPrimeReconstructionHypothesis*)p);
   }
   static void deleteArray_ZPrimeTotTPrimeReconstructionHypothesis(void *p) {
      delete [] ((::ZPrimeTotTPrimeReconstructionHypothesis*)p);
   }
   static void destruct_ZPrimeTotTPrimeReconstructionHypothesis(void *p) {
      typedef ::ZPrimeTotTPrimeReconstructionHypothesis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ZPrimeTotTPrimeReconstructionHypothesis

namespace ROOT {
   static TClass *vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_Dictionary();
   static void vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_TClassManip(TClass*);
   static void *new_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p = 0);
   static void *newArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(Long_t size, void *p);
   static void delete_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p);
   static void deleteArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p);
   static void destruct_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ZPrimeTotTPrimeReconstructionHypothesis>*)
   {
      vector<ZPrimeTotTPrimeReconstructionHypothesis> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ZPrimeTotTPrimeReconstructionHypothesis>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ZPrimeTotTPrimeReconstructionHypothesis>", -2, "vector", 214,
                  typeid(vector<ZPrimeTotTPrimeReconstructionHypothesis>), DefineBehavior(ptr, ptr),
                  &vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_Dictionary, isa_proxy, 4,
                  sizeof(vector<ZPrimeTotTPrimeReconstructionHypothesis>) );
      instance.SetNew(&new_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR);
      instance.SetNewArray(&newArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR);
      instance.SetDelete(&delete_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR);
      instance.SetDeleteArray(&deleteArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR);
      instance.SetDestructor(&destruct_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ZPrimeTotTPrimeReconstructionHypothesis> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<ZPrimeTotTPrimeReconstructionHypothesis>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ZPrimeTotTPrimeReconstructionHypothesis>*)0x0)->GetClass();
      vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEZPrimeTotTPrimeReconstructionHypothesisgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<ZPrimeTotTPrimeReconstructionHypothesis> : new vector<ZPrimeTotTPrimeReconstructionHypothesis>;
   }
   static void *newArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<ZPrimeTotTPrimeReconstructionHypothesis>[nElements] : new vector<ZPrimeTotTPrimeReconstructionHypothesis>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p) {
      delete ((vector<ZPrimeTotTPrimeReconstructionHypothesis>*)p);
   }
   static void deleteArray_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p) {
      delete [] ((vector<ZPrimeTotTPrimeReconstructionHypothesis>*)p);
   }
   static void destruct_vectorlEZPrimeTotTPrimeReconstructionHypothesisgR(void *p) {
      typedef vector<ZPrimeTotTPrimeReconstructionHypothesis> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ZPrimeTotTPrimeReconstructionHypothesis>

namespace ROOT {
   static TClass *vectorlETopJetgR_Dictionary();
   static void vectorlETopJetgR_TClassManip(TClass*);
   static void *new_vectorlETopJetgR(void *p = 0);
   static void *newArray_vectorlETopJetgR(Long_t size, void *p);
   static void delete_vectorlETopJetgR(void *p);
   static void deleteArray_vectorlETopJetgR(void *p);
   static void destruct_vectorlETopJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<TopJet>*)
   {
      vector<TopJet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<TopJet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<TopJet>", -2, "vector", 214,
                  typeid(vector<TopJet>), DefineBehavior(ptr, ptr),
                  &vectorlETopJetgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<TopJet>) );
      instance.SetNew(&new_vectorlETopJetgR);
      instance.SetNewArray(&newArray_vectorlETopJetgR);
      instance.SetDelete(&delete_vectorlETopJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlETopJetgR);
      instance.SetDestructor(&destruct_vectorlETopJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<TopJet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<TopJet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlETopJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<TopJet>*)0x0)->GetClass();
      vectorlETopJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlETopJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlETopJetgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TopJet> : new vector<TopJet>;
   }
   static void *newArray_vectorlETopJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<TopJet>[nElements] : new vector<TopJet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlETopJetgR(void *p) {
      delete ((vector<TopJet>*)p);
   }
   static void deleteArray_vectorlETopJetgR(void *p) {
      delete [] ((vector<TopJet>*)p);
   }
   static void destruct_vectorlETopJetgR(void *p) {
      typedef vector<TopJet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<TopJet>

namespace ROOT {
   static TClass *vectorlEJetgR_Dictionary();
   static void vectorlEJetgR_TClassManip(TClass*);
   static void *new_vectorlEJetgR(void *p = 0);
   static void *newArray_vectorlEJetgR(Long_t size, void *p);
   static void delete_vectorlEJetgR(void *p);
   static void deleteArray_vectorlEJetgR(void *p);
   static void destruct_vectorlEJetgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Jet>*)
   {
      vector<Jet> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Jet>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Jet>", -2, "vector", 214,
                  typeid(vector<Jet>), DefineBehavior(ptr, ptr),
                  &vectorlEJetgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Jet>) );
      instance.SetNew(&new_vectorlEJetgR);
      instance.SetNewArray(&newArray_vectorlEJetgR);
      instance.SetDelete(&delete_vectorlEJetgR);
      instance.SetDeleteArray(&deleteArray_vectorlEJetgR);
      instance.SetDestructor(&destruct_vectorlEJetgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Jet> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<Jet>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEJetgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<Jet>*)0x0)->GetClass();
      vectorlEJetgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEJetgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEJetgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<Jet> : new vector<Jet>;
   }
   static void *newArray_vectorlEJetgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) vector<Jet>[nElements] : new vector<Jet>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEJetgR(void *p) {
      delete ((vector<Jet>*)p);
   }
   static void deleteArray_vectorlEJetgR(void *p) {
      delete [] ((vector<Jet>*)p);
   }
   static void destruct_vectorlEJetgR(void *p) {
      typedef vector<Jet> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<Jet>

namespace ROOT {
   static TClass *maplEstringcOfloatgR_Dictionary();
   static void maplEstringcOfloatgR_TClassManip(TClass*);
   static void *new_maplEstringcOfloatgR(void *p = 0);
   static void *newArray_maplEstringcOfloatgR(Long_t size, void *p);
   static void delete_maplEstringcOfloatgR(void *p);
   static void deleteArray_maplEstringcOfloatgR(void *p);
   static void destruct_maplEstringcOfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,float>*)
   {
      map<string,float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,float>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,float>", -2, "map", 96,
                  typeid(map<string,float>), DefineBehavior(ptr, ptr),
                  &maplEstringcOfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,float>) );
      instance.SetNew(&new_maplEstringcOfloatgR);
      instance.SetNewArray(&newArray_maplEstringcOfloatgR);
      instance.SetDelete(&delete_maplEstringcOfloatgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOfloatgR);
      instance.SetDestructor(&destruct_maplEstringcOfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,float> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,float>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,float>*)0x0)->GetClass();
      maplEstringcOfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOfloatgR(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) map<string,float> : new map<string,float>;
   }
   static void *newArray_maplEstringcOfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) map<string,float>[nElements] : new map<string,float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOfloatgR(void *p) {
      delete ((map<string,float>*)p);
   }
   static void deleteArray_maplEstringcOfloatgR(void *p) {
      delete [] ((map<string,float>*)p);
   }
   static void destruct_maplEstringcOfloatgR(void *p) {
      typedef map<string,float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,float>

namespace {
  void TriggerDictionaryInitialization_SUHH2ZPrimeTotTPrime_dict_Impl() {
    static const char* headers[] = {
"include/ZPrimeTotTPrimeReconstructionHypothesis.h",
0
    };
    static const char* includePaths[] = {
"/nfs/dust/cms/user/abenecke/SFramePhys14",
"/nfs/dust/cms/user/abenecke/CMSSW_7_4_15_patch1/src",
"/cvmfs/cms.cern.ch/slc6_amd64_gcc491/lcg/root/6.02.00-odfocd7/include",
"/nfs/dust/cms/user/abenecke/CMSSW_7_4_15_patch1/src/UHH2/ZPrimeTotTPrime/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$include/ZPrimeTotTPrimeReconstructionHypothesis.h")))  ZPrimeTotTPrimeReconstructionHypothesis;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$string")))  allocator;
}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "include/ZPrimeTotTPrimeReconstructionHypothesis.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ZPrimeTotTPrimeReconstructionHypothesis", payloadCode, "@",
"vector<ZPrimeTotTPrimeReconstructionHypothesis>", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SUHH2ZPrimeTotTPrime_dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SUHH2ZPrimeTotTPrime_dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SUHH2ZPrimeTotTPrime_dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SUHH2ZPrimeTotTPrime_dict() {
  TriggerDictionaryInitialization_SUHH2ZPrimeTotTPrime_dict_Impl();
}
