long long flag_h(long long n/*, t_flag *flags*/) {
    //if (flags->flag_h) {
        n *= 1024;
    //}
    return n;
}

int main() {
	printf("%d\n", flag_h(3003303));
}