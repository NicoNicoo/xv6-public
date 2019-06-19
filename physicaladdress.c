#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc,char *argv[])
{
    char *viraddr;
    viraddr=argv[1];

    printf(1,"introducir direccion virtual: %s\n",viraddr);
    physicaladdress(viraddr);

    exit();
}