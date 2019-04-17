#include <iostream>
#include <string.h>
using namespace std;
class nod
{
    char info;
    nod *next;
    bool ok;
public:
    nod()
    {
        info=' ';
        this->next=NULL;
        ok=true;
    }
    nod(char c)
    {
        info=c;
        this->next=NULL;
        ok=true;
    }
    ~nod()
    {
        if(ok==true) delete next;
    }
    nod(const nod &b)
    {
        ok=false;
    }
    friend istream& operator >>(istream &in, nod& A);
    friend ostream& operator <<(ostream &out, nod& B);
    void operator =(nod &n);
    void set_next(nod*);
    char get_info();
    nod* get_next();
    friend class Coada;
};
istream& operator >>(istream& in, nod& A)
{
    in >> A.info;
    return in;
}
ostream& operator <<(ostream& out, nod& B)
{
    out << B.info;
    return out;
}
void nod::operator=(nod &n)
{
    this->info=n.info;
}
void nod::set_next(nod*a)
{
    this->next=a;
}
char nod::get_info()
{
    return this->info;
}
nod* nod::get_next()
{
    return this->next;
}
class Coada
{
protected:
    nod *prim;
    nod *ultim;
    int dim_max;
    int nr_elem;
    bool ok;
public:
    Coada()
    {
        nr_elem=0;
        prim=NULL;
        ultim=NULL;
        ok=true;
    }
    Coada(char *s);
    ~Coada()
    {
        if (ok==true)
        {
            delete prim;
            delete ultim;
        }
    }
    Coada(const Coada &c)
    {
        ok=false;
    }
    friend istream& operator>>(istream& in, Coada& C);
    friend ostream& operator<<(ostream& out, Coada& C);
    void operator=(Coada &C);
    void add_end(char);
    void delete_beg();
    void set_el(int a)
    {
        nr_elem=a;
    }
    void set_max(int a)
    {
        dim_max=a;
    }
    int get_max()
    {
        return dim_max;
    }
    virtual void add_beg(char c) {};
    virtual void delete_end() {};
};
Coada::Coada(char *s)
{
    cout<<"Introduceti dimensiunea maxima: ";
    cin>>dim_max;
    int l=strlen(s);
    if(dim_max>l) nr_elem=l;
    else nr_elem=dim_max;
    nod *n=new nod(s[0]);
    prim=n;
    ultim=n;
    for(int i=1; i<l && i<dim_max; i++)
    {
        n=new nod(s[i]);
        ultim->next=n;
        ultim=n;
    }
    if(l>dim_max) cout<<"Queue overflow - urmatoarele caractere nu au putut fi introduse in coada: ";
    for(int i=dim_max; i<l; i++)
    {
        cout<<s[i];
    }
    ok=true;
}
istream& operator>>(istream& in, Coada& C)
{
    cout<<"Care este dimensiunea maxima a cozii? ";
    in >> C.dim_max;
    cout<<"Cate elemente va avea coada? :";
    in >> C.nr_elem;
    char c;
    nod *n;
    for(int i=0; i<C.nr_elem && i<C.dim_max; i++)
    {
        in >> c;
        n=new nod(c);
        if(i==0)
        {
            C.prim=n;
            C.ultim=n;
        }
        else
        {
            C.ultim->set_next(n);
            C.ultim=n;
        }

    }
    if(C.nr_elem>C.dim_max)
    {
        cout<<"\nQueue overflow - urmatoarele elemente nu au avut loc in coada: ";
        for(int i=C.dim_max; i<C.nr_elem; i++)
        {
            in>>c;
            cout<<c;
        }
        C.nr_elem=C.dim_max;
    }
    return in;
}
ostream& operator<<(ostream& out, Coada& C)
{
    nod* ptr;
    ptr=C.prim;
    out<<endl;
    do
    {
        out << ptr->get_info();
        ptr=ptr->get_next();
    }
    while (ptr!=C.ultim);
    out<<ptr->get_info();
    return out;
}
void Coada::operator=(Coada& C)
{

    nr_elem=C.nr_elem;
    dim_max=C.dim_max;
    prim=NULL;
    ultim=NULL;
    nod* n;
    nod* t;
    t=C.prim;
    n=new nod(t->get_info());
    prim=n;
    ultim=n;
    t=t->get_next();
    while(t!=C.ultim)
    {
        n=new nod(t->get_info());
        ultim->set_next(n);
        ultim=n;
        t=t->get_next();
    }
    n=new nod(t->get_info());
    ultim->set_next(n);
    ultim=n;
}
void Coada::add_end(char c)
{
    if(nr_elem>=dim_max) cout<<"\nQueue overflow - elementul "<<"'"<<c<<"' nu a putut fi introdus.\n";
    else
    {
        nod*n=new nod(c);
        if(ultim!=NULL)
            ultim->set_next(n);
        ultim=n;
        nr_elem++;
    }
}
void Coada::delete_beg()
{
    if(prim==NULL) return;
    nod *temp=prim;
    prim=prim->next;
    cout<<prim->info;
    cout<<temp->info;
    delete temp;
    nr_elem--;
}
class Dequeue:public Coada
{
    bool k;
public:
    Dequeue(char*s):Coada(s)
    {
        k=true;
    }
    Dequeue():Coada()
    {
        k=true;
    }
    Dequeue(const Dequeue &ob):Coada(ob)
    {
        k=false;
    }
    ~Dequeue()
    {
        if(k==true) delete this;
    }
    void add_beg(char c);
    void delete_end();
    friend istream& operator>>(istream&, Dequeue&);
    friend ostream& operator<<(ostream&, Dequeue&);
    void operator=(const Dequeue& d);
};
void Dequeue::add_beg(char c)
{
    if(nr_elem>=dim_max)
    {
        cout<<"\nOverflow ";
        return;
    }
    nod* node=new nod(c);
    node->set_next(prim);
    prim=node;
    nr_elem++;
}
void Dequeue::delete_end()
{
    if(prim==NULL) return;
    nod* temp=prim;
    while(temp->get_next()!=ultim)
    {
        temp=temp->get_next();
    }
    temp->set_next(NULL);
    nod* aux=temp;
    temp=ultim;
    ultim=aux;
    delete temp;
    nr_elem--;
}
istream& operator>>(istream& in, Dequeue& d)
{
    cout<<"Dimensiune maxima dequeue: ";
    in >> d.dim_max;
    cout<<"Dimensiune dequeue: ";
    int aux;
    in>>aux;
    char c;
    for(int i=0; i<aux && i<d.dim_max; i++)
    {
        in >> c;
        d.add_end(c);
    }
    d.nr_elem=aux;
    if(d.nr_elem>d.dim_max) cout<<"Overflow";
    return in;
}
ostream & operator<<(ostream& out, Dequeue& d)
{
    nod* temp=d.prim;
    while(temp!=NULL)
    {
        out<<temp->get_info();
        temp=temp->get_next();
    }
    return out;
}
void Dequeue::operator=(const Dequeue& d)
{
    nr_elem=d.nr_elem;
    dim_max=d.dim_max;
    nod* t;
    nod* u;
    nod* node;
    t=NULL;
    u=d.prim;
    while(u!=NULL)
    {
        node=new nod(u->get_info());
        t->set_next(node);
        u=u->get_next();
    }
}
class DequeM:protected Coada
{
    bool k;
public:
    DequeM(char *s):Coada(s)
    {
        k=true;
    }
    DequeM():Coada()
    {
        k=true;
    }
    DequeM(const DequeM &m):Coada(m)
    {
        k=false;
    }
    ~DequeM()
    {
        if(k==true) delete this;
    }
    void add_beg(char c);
    void delete_beg();
    void delete_end();
    friend istream& operator>>(istream& in, DequeM& m);
    friend ostream& operator<<(ostream& out, DequeM& m);
    void operator=(const DequeM& m);
};
void DequeM::add_beg(char c)  //am considerat adaugarea si stergerea (daca exista mai mult de un element) la inceput facandu-se dupa nodul marcaj
{
    if(nr_elem>=dim_max)
    {
        cout<<"\nOverflow ";
        return;
    }
    nod* node=new nod(c);
    if(prim==NULL)
    {
        prim=node;
    }
    else
    {
        nod* aux;
        aux=prim->get_next();
        node->set_next(aux);
        prim->set_next(node);
    }
    nr_elem++;
}
void DequeM::delete_beg()
{
    if(prim==NULL) return;
    if(prim->get_next()==NULL)
    {
        delete prim;
        prim=NULL;
    }
    else
    {
        nod* a1;
        nod* a2;
        a1=prim->get_next();
        a2=a1->get_next();
        prim->set_next(a2);
        delete a1;
    }
    nr_elem--;
}
void DequeM::delete_end()
{
    if(prim==NULL) return;
    nod* temp=prim;
    while(temp->get_next()!=ultim)
    {
        temp=temp->get_next();
    }
    temp->set_next(NULL);
    nod* aux=temp;
    temp=ultim;
    ultim=aux;
    delete temp;
    nr_elem--;
}
istream& operator>>(istream& in, DequeM& d)
{
    cout<<"Dimensiune maxima dequeueM: ";
    in >> d.dim_max;
    cout<<"Dimensiune dequeueM: ";
    in >> d.nr_elem;
    char c;
    for(int i=0; i<d.nr_elem && i<d.dim_max; i++)
    {
        in >> c;
        d.add_end(c);
    }
    if(d.nr_elem>d.dim_max) cout<<"Overflow";
    return in;
}
ostream & operator<<(ostream& out, DequeM& d)
{
    nod* temp=d.prim;
    while(temp!=NULL)
    {
        out<<temp->get_info();
        temp=temp->get_next();
    }
    return out;
}
void DequeM::operator=(const DequeM& d)
{
    nr_elem=d.nr_elem;
    dim_max=d.dim_max;
    nod* t;
    nod* u;
    nod* node;
    t=NULL;
    u=d.prim;
    while(u!=NULL)
    {
        node=new nod(u->get_info());
        t->set_next(node);
        u=u->get_next();
    }
}
int main()
{

    return 0;
}
