
## Introduction

> OpenMP is a set of compiler`s directives, library procedures and environment variables which was developed for creating multi-threading apps for systems with shared memory

### A hello world program

```cpp
#include <iostream>

using namespace std;

int main(){

	#pragma omp parallel
	cout<<"Hello!"<<endl;
	return 0;
}
```

> To compile use the `-fopenmp` flag

### Controlling the number of threads used

```cpp
#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;

#define NUMBER_OF_THREADS 4

int main(){

	omp_set_num_threads(NUMBER_OF_THREADS);
	#pragma omp parallel
	{
		sleep(3 * omp_get_thread_num());
		cout<<"Hello from Thread "<<omp_get_thread_num()<<endl;
	}
}
```

Alternate way, instead of line 11, 

```cpp
#pragma omp parallel num_threads(NUMBER_OF_THREADS)
```

### OMP For with time comparision

```cpp
#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;  

#define ARRAY_SIZE 5

int main()
{
	int *arr = new int[ARRAY_SIZE];
	#pragma omp parallel for
	
	for(int i=0;i<ARRAY_SIZE;i++){
		sleep(1);
		arr[i] = i*10;
	}
	return 0;
}
```

Run as `time ./a.out` to get the execution time

### Barrier and critical directive

#### Barrier

The barrier directive stops all processes for proceeding to the next line of code until all processes have reached the barrier. This allows a programmer to synchronize sequences in the parallel process.
```cpp
#pragma omp barrier
```
Example snippet,
```cpp
#include <iostream>\
#include <omp.h>

using namespace std;

#define NUMBER_OF_THREADS 4

int main(){

	#pragma omp parallel num_threads(NUMBER_OF_THREADS)
	{
		cout<<"Hi from thread "<<omp_get_thread_num()<<endl;
		#pragma omp barrier
		cout<<"Bye from thread "<<omp_get_thread_num()<<endl;
	}
	return 0;
}
```

#### Critical

A critical directive ensures that a line of code is only run by one process at a time, ensuring thread safety in the body of code.
```cpp
#pragma omp critical { … }
```


### Private vs Shared variables

```cpp
#pragma omp shared(shar_Var1) private(priv_Var1, priv_Var2)
```

-   Private types create a copy of a variable for each process in the parallel system.
-   Shared types hold one instance of a variable for all processes to share.

- Variables that are created and assigned inside of a parallel section of code will be inherently be private 
- Variables created outside of parallel sections will be inherently public.

```cpp
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
	int sh=1, pv=3;
	
	#pragma omp parallel shared(sh) private(pv)
	{
		#pragma omp critical	
		{
			cout<<"thread: "<<omp_get_thread_num()<<endl;
			cout<<"pv val: "<<pv<<endl;
			cout<<"sh val: "<<sh<<endl<<endl;
			sh++;	
			pv++;
		}
	}
	return 0;
}
```

> Note: *Private int's intial value inside each thread will be 0*

