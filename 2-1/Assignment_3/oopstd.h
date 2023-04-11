namespace oopstd {
	void* memset(void* ptr, int value, size_t num);
	void* memcpy(void* destination, const void* source, size_t num);

	int strcmp(const char* str1, const char* str2);
	int strncmp(const char* str1, const char* str2, size_t num);

	char* strcpy(char* destination, const char* source);
	char* strncpy(char* destination, const char* source, size_t num);

	size_t strlen(const char* str);

	int atoi(const char* str);
	float atof(const char* str);
}