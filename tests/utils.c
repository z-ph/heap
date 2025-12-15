#include "../src/heap.c"

#define COLOR_GREEN "\033[32m"
#define COLOR_RED "\033[31m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

int expect(int a, int b, const char *test_name)
{
    if (a == b)
    {
        printf("%s[PASS]%s %s\n", COLOR_GREEN, COLOR_RESET, test_name);
        return 1;
    }
    else
    {
        printf("%s[FAIL]%s %s: expected %d, got %d\n", COLOR_RED, COLOR_RESET, test_name, b, a);
        return 0;
    }
}
void print_info(const char *info)
{
    printf("\n%s- %s %s\n", COLOR_BLUE, info, COLOR_RESET);
}

void print_heap_array(Element *array, int size, const char *label)
{
    printf("%s%s%s [", COLOR_BLUE, label, COLOR_RESET);
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i + 1].key);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}
void print_normal_array(Element *array, int size, const char *label)
{
    printf("%s%s%s [", COLOR_BLUE, label, COLOR_RESET);
    for (int i = 0; i < size; i++)
    {
        printf("%d", array[i].key);
        if (i < size - 1)
            printf(", ");
    }
    printf("]\n");
}
int expect_heap_array_equal(Element *actual, int size, Element *expected, int expected_size, const char *test_name)
{
    if (size != expected_size)
    {
        printf("%s[FAIL]%s %s: expected size %d, got %d\n", COLOR_RED, COLOR_RESET, test_name, expected_size, size);
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        if (actual[i + 1].key != expected[i + 1].key)
        {
            printf("%s[FAIL]%s %s: at index %d expected %d, got %d\n", COLOR_RED, COLOR_RESET, test_name, i, expected[i + 1].key, actual[i + 1].key);
            print_heap_array(actual, size, "Actual");
            print_heap_array(expected, expected_size, "Expected");
            return 0;
        }
    }

    printf("%s[PASS]%s %s\n", COLOR_GREEN, COLOR_RESET, test_name);
    return 1;
}
int expect_normal_array_equal(Element *actual, int size, Element *expected, int expected_size, const char *test_name)
{
    if (size != expected_size)
    {
        printf("%s[FAIL]%s %s: expected size %d, got %d\n", COLOR_RED, COLOR_RESET, test_name, expected_size, size);
        return 0;
    }

    for (int i = 0; i < size; i++)
    {
        if (actual[i].key != expected[i].key)
        {
            printf("%s[FAIL]%s %s: at index %d expected %d, got %d\n", COLOR_RED, COLOR_RESET, test_name, i, expected[i].key, actual[i].key);
            print_normal_array(actual, size, "Actual");
            print_normal_array(expected, expected_size, "Expected");
            return 0;
        }
    }

    printf("%s[PASS]%s %s\n", COLOR_GREEN, COLOR_RESET, test_name);
    return 1;
}