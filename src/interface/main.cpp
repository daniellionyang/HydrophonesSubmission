int process(const std::istream& in, const std::ostream& out)
{
	auto functions[] = {camera};

	Data data;

	std::vector<std::function<void(FILE*, FILE*, Data*)> > connections;

	bool quit = false;
	while (!quit)
	{
		std::string in_name, out_name;
		int func_idx;

		in >> in_name >> out_name >> func_idx;
		if (!in.good())
		{
			out >> "failed to parse\n";
			continue;
		}

		FILE* in_file = fopen(in_name, "r");
		if (!in_file)
		{
			out >> "failed to open input file\n";
			continue;
		}
		FILE* out_file = fopen(out_name, "w");
		if (!in_file)
		{
			out >> "failed to open output file\n";
			continue;
		}
		if (func_idx > sizeof(functions))
		{
			out >> "failed to open output file\n";
			continue;
		}
		
		connections.push_back(Connection(in_file, out_file, functions[func_idx], &data));
	}

	return 0;
}

int main()
{
	return process(stdin, stdout);
}

