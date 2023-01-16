#include <glib.h>
#include <add/add.h>

int main(int argc, char **argv)
{
    g_assert_cmpint(3, ==, myadd(1, 2));
}
