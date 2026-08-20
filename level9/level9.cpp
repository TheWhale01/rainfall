#include <cstddef>
#include <cstring>

class N
{
    public:
        N(int param1)
        {
            attr = param1;
            return;
        }

        void setAnnotation(char *str)
        {
            size_t n = strlen(str);
            memcpy(this + 4, str, n);
            return;
        }

        virtual int operator+(N &inst)
        {
            return inst.attr + attr;
        }

        virtual int operator-(N &inst)
        {
            return inst.attr - attr;
        }

        int attr;
};

int main(int ac, char **av)
{
    N *inst;
    N *inst1;

    if (ac < 2)
    {
        _exit(1);
    }
    inst = new N(5);
    inst1 = new N(6);
    inst->setAnnotation(av[1]);

    (*inst) + (*inst1);
    return 0;
}
