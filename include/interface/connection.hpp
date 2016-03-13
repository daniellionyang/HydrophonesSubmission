class Connection
{
public:
	Connection(FILE*, FILE*, std::function<void(FILE*, FILE*, Data*)>, Data*);
	~Connection();

private:
	FILE* in;
	FILE* out;
	std::function<void(FILE*, FILE*, Data*)> function;
	Data* data;
	std::thread thread;
};

