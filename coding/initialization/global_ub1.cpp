int DynamicCompute(int n)
{
    return n * n;
}

// "const" or "static" could limit variable scope to current tranlation unit
int a = DynamicCompute(10);

constexpr int StaticCompute(int n)
{
    return n * n;
}
// "constexpr" could make this variable bound to current tranlation unit
constinit int safeA = StaticCompute(10);
