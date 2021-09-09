#define DEBUG
#ifndef PLTOBJECT_H_
#define PLTOBJECT_H_
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
#define PltList vector<PltObject>
#define PltArgs const vector<PltObject>&
#define Dictionary std::unordered_map<PltObject,PltObject,PltObject::HashFunction>
struct PltObject;
typedef PltObject(*Method)(PltObject&,const vector<PltObject>&);
typedef PltObject(*func)(const vector<PltObject>&);
struct NativeObject;
size_t hashList(void*);
size_t hashDict(void*);
enum ErrCode
{
  SYNTAX_ERROR = 1,
  TYPE_ERROR = 2,
  VALUE_ERROR = 3,
  MATH_ERROR  = 4,
  NAME_ERROR = 5,
  INDEX_ERROR = 6,
  UNKNOWN_ERROR = 7
};


NativeObject* NewNativeObject(void*);
struct PltObject
{
    union
    {
        void* ptr;
        float f;
        long long int l;
        int i;
    };
    char type;
    string s;
    bool active;//whether the memory pointed by pointer is active or is deleted
    PltObject()
    {
        ptr = nullptr;
        active = false;
        type = 'n';
    }
    PltObject(int x)
    {
        type = 'i';
        i = x;
        active = false;
    }
    PltObject(string x)
    {
        type = 's';
        s = x;
        active = false;
    }
    PltObject(Method e)
    {
      ptr = (void*)e;
      type = 'r';
      active = false;
    }
    PltObject(NativeObject);
    PltObject(long long int x)
    {
        type = 'l';
        l = x;
        active = false;
    }
    PltObject(FILE* fp)
    {
        type = 'u';
        ptr = (void*)fp;
        active = true;
    }
    PltObject(const PltList& x)
    {
        type = 'j';
        PltList* p = new PltList(x);
        ptr = (void*)p;
        active = true;
    }
    PltObject(bool x)
    {
        type = 'b';
        i = x;
        active = false;
    }
    PltObject(float x)
    {
        type = 'f';
        f = x;
        active = false;
    }
    PltObject(unsigned char x)
    {
        type = 'm';
        i = x;
        active = false;
    }
    PltObject(const PltObject& other)
    {
        type = other.type;
        if(other.type=='i')
        {
           i = other.i;
           active = false;
        }
        else if(other.type=='n')
        {

        }
        else if(other.type=='r')
        {
          ptr = other.ptr;
          active = false;
        }
        else if(other.type=='f')
        {
           f = other.f;
           active = false;
        }
        else if(other.type=='q')
        {
          ptr = other.ptr;
          type = 'q';
        }
        else if(other.type=='e')
        {
           s = other.s;
           i = other.i;
           active = false;
        }
        else if(other.type=='b')
        {
            i = other.i;
            active = false;
        }
        else if(other.type=='c')
        {
                   ptr = (void*)NewNativeObject(other.ptr);
           type = 'c';
           active = true;
        }
        else if(other.type=='s')
        {
           s = other.s;
           active = false;
        }
        else if(other.type=='u')
        {
            ptr = other.ptr;
        }
        else if(other.type=='m')
        {
            i = other.i;
            active = false;
        }
        else if(other.type=='j')
        {
          PltList l = *(PltList*)other.ptr;
          PltList* p = new PltList(l);
          if(!p)
          {
              printf("Unable to allocate memory\n");
              exit(0);
          }
          ptr = (void*)p;
          active = true;
        }
        else if(other.type=='l')
        {
            l = other.l;
            active = false;
        }
        else if(other.type=='a')
        {
          Dictionary* p = new Dictionary(*(Dictionary*)other.ptr);
          if(!p)
          {
              printf("Unable to allocate memory\n");
              exit(0);
          }
          ptr = (void*)p;
          active = true;
        }
    }
    void operator=(const PltObject& other)
    {
      //   printf("assigning using operator\n");
        destroy();
        type = other.type;
        if(other.type=='i')
        {
           i = other.i;
           active = false;
        }
        else if(other.type=='n')
        {

        }
        else if(other.type=='r')
        {
          ptr = other.ptr;
          type = 'r';
          active = false;
        }
        else if(other.type=='f')
        {
           f = other.f;
           active = false;
        }
        else if(other.type=='e')
        {
           s = other.s;
           i = other.i;
           active = false;
        }
        else if(other.type=='c')
        {
           ptr = (void*)NewNativeObject(other.ptr);
           type = 'c';
           active = true;
        }
        else if(other.type=='q')
        {
           ptr = other.ptr;
           type = 'q';
        }
        else if(other.type=='b')
        {
            i = other.i;
            active = false;
        }
        else if(other.type=='s')
        {
           s = other.s;
           active = false;
        }
        else if(other.type=='u')
        {
            ptr = other.ptr;
        }
        else if(other.type=='m')
        {
           i = other.i;
           active = false;
        }
        else if(other.type=='j')
        {
          PltList* p = new PltList(*(PltList*)other.ptr);
          ptr = (void*)p;
          active = true;
        }
        else if(other.type=='l')
        {
            l = other.l;
            active = false;
        }
        else if(other.type=='a')
        {
          Dictionary* p = new Dictionary(*(Dictionary*)other.ptr);
          if(!p)
          {
              printf("Unable to allocate memory\n");
              exit(0);
          }
          ptr = (void*)p;
          active = true;
        }
    }
    void operator=(int x)
    {
        destroy();
        type = 'i';
        i = x;
        active = false;
    }
    void operator=(Method x)
    {
        destroy();
        type = 'r';
        ptr = (void*)x;
        active = false;
    }

    void operator=(FILE* x)
    {
        destroy();
        type = 'u';
        ptr = (void*)x;
        active = true;
    }
    void operator=(long long int x)
    {
        destroy();
        type = 'l';
        l = x;
        active = false;
    }
    void operator=(bool x)
    {
        destroy();
        type = 'b';
        i = x;
        active = false;
    }
    void operator = (float x)
    {
        destroy();
        type = 'f';
        f = x;
        active = false;
    }
    void operator = (unsigned char x)
    {
        destroy();
        type = 'm';
        i = x;
        active = false;
    }
    void operator=(NativeObject);
    void operator = (string x)
    {
        destroy();
        type = 's';
        s = x;
        active = false;
    }
    void destroy()
    {

        if(!active)
            return;
        if(type=='j')
        {
          PltList* p = (PltList*)ptr;
          delete p;
        }
        else if(type=='a')
        {
          Dictionary* p = (Dictionary*)ptr;
          delete p;
        }
        else if(type=='c')
        {
          NativeObject* p = (NativeObject*)ptr;
          delete p;
        }
        active = false;
    }
    ~PltObject()
    {
      if(active)
        destroy();
    }
    bool operator==(const PltObject& other)const
    {
        if(other.type!=type)
            return false;
        if(type=='n')
        {
          return true;
        }
        else if(type=='i')
        {
          return i==other.i;
        }
        else if(type=='l')
        {
          return l==other.l;
        }
        else if(type=='f')
        {
          return f==other.f;
        }
        else if(type=='b')
        {
          return i==other.i;
        }
        else if(type=='m')
        {
          return i==other.i;
        }
        else if(type=='u')
        {
          return ((FILE*)ptr)==((FILE*)other.ptr);
        }
        else if(type=='s')
        {
          return other.s==s;
        }
        else if(type=='j')
        {
            PltList a = *(PltList*)ptr;
            PltList b = *(PltList*)other.ptr;
            return a==b;
        }
        else if(type=='q')
        {
          return false;
        }
        else if(type=='a')
        {
            Dictionary a = *(Dictionary*)ptr;
            Dictionary b = *(Dictionary*)other.ptr;
            return a==b;
        }
        return false;
    }
    struct HashFunction
    {
      size_t operator()(const PltObject& obj) const
      {
        size_t a = std::hash<char>()(obj.type);
        size_t b;
        size_t hashPltObject(const PltObject&);
        b = hashPltObject(obj) << 1;
        return a ^ b;
      }
  };
};
size_t hashPltObject(const PltObject&);
size_t hashList(void* p)
{
  PltList l = *(PltList*)p;
   size_t hash = l.size();
   for (auto i : l)
      hash ^= hashPltObject(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    return hash;
}
size_t hashDict(void* p)
{
  Dictionary d = *(Dictionary*)p;
   size_t hash = d.size();
    for (auto i : d)
      hash ^= hashPltObject(i.first)+hashPltObject(i.second) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    return hash;
}
size_t hashPltObject(const PltObject& a)
{
    char t = a.type;
    if(t=='s')
    {
        return std::hash<std::string>()(a.s);
    }
    else if(t=='i')
    {
        return std::hash<int>()(a.i);
    }
    else if(t=='l')
    {
        return std::hash<long long int>()(a.l);
    }
    else if(t=='f')
    {
        return std::hash<float>()(a.f);
    }
    else if(t=='j')
    {
        return hashList(a.ptr);
    }
    else if(t=='a')
    {
        return hashDict(a.ptr);
    }
    else if(t=='u')
    {
        return std::hash<FILE*>()((FILE*)a.ptr);
    }
    else if(t=='m')
    {
        return std::hash<unsigned char>()(a.i);
    }
    else if(t=='b')
    {
        return std::hash<bool>()(a.i);
    }
    return 0;
}
struct NativeObject
{
   void* ptr;
   Dictionary attr;
};
void PltObject::operator=(NativeObject x)
{
        destroy();
        type = 'c';
        NativeObject* p = new NativeObject(x);
        ptr = (void*)p;
        active = true;;
}
PltObject::PltObject(NativeObject x)
{
             ptr = (void*) new NativeObject(x);
           type = 'c';
           active = true;
}
NativeObject* NewNativeObject(void* x)
{

  NativeObject* p = new NativeObject(*(NativeObject*)x);
  return p;
}
PltObject Plt_Err(ErrCode e,string des)
{
  PltObject ret;
  ret.type = 'e';
  ret.s = des;
  ret.i = e;
  return ret;
}

#endif
