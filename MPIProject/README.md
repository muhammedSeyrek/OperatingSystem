 
#programin derlenmesi, calistirilmasi ve object dosyalarinin kaldirilmasi islemleri:
	Makefile dosyasinda hepsini derlemek icin bir yapı olusturuldu.
	Kullanicinin yapmasi gerekenler:
		Derlemek icin : make komutu girilmeli
		Semaforlu yapiyi calistirmak icin: ./hello 10 (proses sayisi)
		MPI olan programi çalistirmak icin: mpirun -np 10 ./myMpiRun diyoruz.
		Programin object dosyalarini silmek ve tekrar derlendiginde sorun olmamasi icin: make clean komutu ile temizliyoruz.
