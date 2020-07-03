#include <cstdlib>
#include <iostream>
#include <cstring>
#include <chrono>
#include <SFML\Graphics.hpp>
#define NORMALIZE 6 + ((((time_spent_normal[i] - min) * 1688) + (max - min)) / (max - min) / 2)
#define NORMALIZEB 6 + ((((time_spent_bigrange[i] - min) * 1688) + (max - min)) / (max - min) / 2)

void pigeonholeSort(long int arr[], int n) {

	long int min = arr[0], max = arr[0];
	int i, j, index = 0;
	//dizide max ve min bulma
	for (i = 1; i < n; i++) {
		if (arr[i] < min)
			min = arr[i];
		if (arr[i] > max)
			max = arr[i];
	}
	//dizinin range'ini bulma
	long int range = max - min + 1;
	//dizinin elemanlarýnýn tutulacaðý pigeon hollerin açýlmasý
	int* phole = (int*)malloc(range * sizeof(int));
	memset(phole, 0, range * sizeof(int));
	//elemanlarýn pigeon hollere yerleþtirilmesi
	for (i = 0; i < n; i++)
		phole[arr[i] - min]++;
	//pigeon hollerdeki elemanlarýn tekrardan diziye geri konulmasý
	for (j = 0; j < range; j++) {
		while (phole[j]-- > 0) {
			arr[index++] = j + min;
		}
	}
}


int main() {
	int i;
	double time_spent_normal[4] = {};
	double time_spent_bigrange[4] = {};

	/* sýrayla 1.000, 10.000 ve 100.000 elemanlý 2'þer dosya, toplam 6 dosya okunup diziye aktarýlýyor.
	pigeonhole sorting, dizinin eleman sayýsý ve range'i birbirine ne kadar yakýnsa teoride o kadar hýzlý çalýþtýðý
	için, range'i eleman sayýsýyla eþit olan ve range'i eleman sayýsýnýn 10 katý fazla olan 2 farklý dizi sýralanýyor.
	bu iþlemlerin süresi std::chrono::high_resolution_clock ile nanometre hassaslýðýnda ölçülüyor.*/



	long int* arr_1000 = (long int*)malloc(1000 * sizeof(long int));
	//dosyanýn okunup diziye aktarýlmasý
	FILE* arr1000 = fopen("1000.txt", "r");
	for (i = 0; i < 1000; i++) {
		fscanf(arr1000, "%d", &arr_1000[i]);
	}
	//pigeonholeSort fonksiyonunun çaðýrýlýp dizinin sýralanmasý, ayný zamanda sýralanýrken geçen süre de ölçülüyor
	auto start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_1000, 1000);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_normal[0] = duration;
	fclose(arr1000);
	//yukarýdaki ayný iþlem, range'i dizinin eleman sayýsýndan 10 kat fazla olan baþka bir dizi için de yapýlýyor
	FILE* arr1000_ = fopen("bigger_range_1000.txt", "r");
	for (i = 0; i < 1000; i++) {
		fscanf(arr1000_, "%d", &arr_1000[i]);
	}
	start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_1000, 1000);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_bigrange[0] = duration;
	fclose(arr1000_);
	free(arr_1000);

	//ayný iþlem 10.000 eleman sayýlý dizi için yapýlýyor

	long int* arr_10000 = (long int*)malloc(10000 * sizeof(long int));
	FILE* arr10000 = fopen("10000.txt", "r");
	for (i = 0; i < 10000; i++) {
		fscanf(arr10000, "%d", &arr_10000[i]);
	}
	start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_10000, 10000);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_normal[1] = duration;
	fclose(arr10000);
	FILE* arr10000_ = fopen("bigger_range_10000.txt", "r");
	for (i = 0; i < 10000; i++) {
		fscanf(arr10000_, "%d", &arr_10000[i]);
	}
	start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_10000, 10000);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_bigrange[1] = duration;
	fclose(arr10000_);
	free(arr_10000);

	//ayný iþlem 100.000 eleman sayýlý dizi için yapýlýyor

	long int* arr_100000 = (long int*)malloc(100000 * sizeof(long int));
	FILE* arr100000 = fopen("100000.txt", "r");
	for (i = 0; i < 100000; i++) {
		fscanf(arr100000, "%d", &arr_100000[i]);
	}
	start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_100000, 100000);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_normal[2] = duration;
	fclose(arr100000);
	FILE* arr100000_ = fopen("bigger_range_100000.txt", "r");
	for (i = 0; i < 100000; i++) {
		fscanf(arr100000_, "%d", &arr_100000[i]);
	}
	start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_100000, 100000);
	end = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_bigrange[2] = duration;
	fclose(arr100000_);
	free(arr_100000);

	/*süre ölçümleri arasýndaki fark çok fazla olduðu için(binlerce hatta onbinlerce kat fark var),
	bu sürelerin normalize edilmesi gerekiyor. bu yüzden minimum ve maksimum diziler bulunup süreler
	normalize ediliyor(6 ve 850 arasýnda)*/

	double min, max;
	min = time_spent_normal[0];
	max = time_spent_normal[0];
	for (i = 1; i < 3; i++) {
		if (time_spent_normal[i] < min) {
			min = time_spent_normal[i];
		}
		if (time_spent_normal[i] > max) {
			max = time_spent_normal[i];
		}
		if (time_spent_bigrange[i] < min) {
			min = time_spent_bigrange[i];
		}
		if (time_spent_bigrange[i] > max) {
			max = time_spent_bigrange[i];
		}
	}


	for (i = 0; i < 3; i++) {
		time_spent_normal[i] = NORMALIZE; //NORMALIZE VE NORMALIZEB kodun en üstünde tanýmlanmýþ birer makro
		time_spent_bigrange[i] = NORMALIZEB;
	}

	printf("          RANGE = ELEMAN SAYISI                   RANGE = ELEMAN SAYISI * 10\n\n");
	for (i = 0; i < 3; i++) {
		printf("           %f birim sure                        %f birim sure\n\n", time_spent_normal[i], time_spent_bigrange[i]);
	}
	//Burdan sonrasý verilerin ekrana yazdýrýlmasý. Ekrana yazdýrýrken SFML kullandým (VS19 üzerinde)

	//ekrana çýkacak yazýlarýn fontu
	sf::Font font;
	if (!font.loadFromFile("font.otf")) {
		printf("\n Font yuklenirken hata olustu\n");
	}

	//ekranýn boyutu, 1280x1000
	sf::RenderWindow window(sf::VideoMode(1280, 1000), "Pigeonhole Sort Verileri");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		
		//X ve Y koordinatlarýnýn ekrana çizilmesi
		
		sf::RectangleShape y_axis(sf::Vector2f(1.0, 860.0));
		y_axis.setPosition(120, 40);
		y_axis.setFillColor(sf::Color::White);
		window.draw(y_axis);
		sf::RectangleShape x_axis(sf::Vector2f(1100.0, 1.0));
		x_axis.setPosition(120, 900);
		x_axis.setFillColor(sf::Color::White);
		window.draw(x_axis);

		//range = eleman sayýsý olan dizilerin ekrana çizilmesi
		
		sf::RectangleShape t0(sf::Vector2f(100.0, time_spent_normal[0]));
		t0.setPosition(160, 900 - time_spent_normal[0]);
		t0.setFillColor(sf::Color::Green);
		window.draw(t0);

		sf::RectangleShape t1(sf::Vector2f(100.0, time_spent_normal[1]));
		t1.setPosition(490, 900 - time_spent_normal[1]);
		t1.setFillColor(sf::Color::Green);
		window.draw(t1);
		
		sf::RectangleShape t2(sf::Vector2f(100.0, time_spent_normal[2]));
		t2.setPosition(820, 900 - time_spent_normal[2]);
		t2.setFillColor(sf::Color::Green);
		window.draw(t2);
		
		//range = eleman sayýsý * 10 olan dizilerin ekrana çizilmesi

		sf::RectangleShape t0_b(sf::Vector2f(100.0, time_spent_bigrange[0]));
		t0_b.setPosition(290, 900 - time_spent_bigrange[0]);
		t0_b.setFillColor(sf::Color::Red);
		window.draw(t0_b);

		sf::RectangleShape t1_b(sf::Vector2f(100.0, time_spent_bigrange[1]));
		t1_b.setPosition(620, 900 - time_spent_bigrange[1]);
		t1_b.setFillColor(sf::Color::Red);
		window.draw(t1_b);

		sf::RectangleShape t2_b(sf::Vector2f(100.0, time_spent_bigrange[2]));
		t2_b.setPosition(950, 900 - time_spent_bigrange[2]);
		t2_b.setFillColor(sf::Color::Red);
		window.draw(t2_b);

		//yazýlarýn ekrana çizilmesi

		sf::Text text_1000;
		text_1000.setFont(font);
		text_1000.setString("Dizi Boyutu = 1000");
		text_1000.setFillColor(sf::Color::White);
		text_1000.setCharacterSize(20);
		text_1000.setPosition(sf::Vector2f(170.0, 920));
		window.draw(text_1000);

		
		sf::Text value1_1000;
		value1_1000.setFont(font);
		value1_1000.setString(std::to_string(time_spent_normal[0]));
		value1_1000.setFillColor(sf::Color::Green);
		value1_1000.setCharacterSize(15);
		value1_1000.setPosition(sf::Vector2f(165.0, 870 - time_spent_normal[0]));
		window.draw(value1_1000);

		sf::Text value2_1000;
		value2_1000.setFont(font);
		value2_1000.setString(std::to_string(time_spent_bigrange[0]));
		value2_1000.setFillColor(sf::Color::Red);
		value2_1000.setCharacterSize(15);
		value2_1000.setPosition(sf::Vector2f(298.0, 870 - time_spent_bigrange[0]));
		window.draw(value2_1000);

		sf::Text text_10000;
		text_10000.setFont(font);
		text_10000.setString("Dizi Boyutu = 10000");
		text_10000.setFillColor(sf::Color::White);
		text_10000.setCharacterSize(20);
		text_10000.setPosition(sf::Vector2f(495.0, 920));
		window.draw(text_10000);

		sf::Text value1_10000;
		value1_10000.setFont(font);
		value1_10000.setString(std::to_string(time_spent_normal[1]));
		value1_10000.setFillColor(sf::Color::Green);
		value1_10000.setCharacterSize(15);
		value1_10000.setPosition(sf::Vector2f(493.0, 870 - time_spent_normal[1]));
		window.draw(value1_10000);

		sf::Text value2_10000;
		value2_10000.setFont(font);
		value2_10000.setString(std::to_string(time_spent_bigrange[1]));
		value2_10000.setFillColor(sf::Color::Red);
		value2_10000.setCharacterSize(15);
		value2_10000.setPosition(sf::Vector2f(625.0, 870 - time_spent_bigrange[1]));
		window.draw(value2_10000);



		sf::Text text_100000;
		text_100000.setFont(font);
		text_100000.setString("Dizi Boyutu = 100000");
		text_100000.setFillColor(sf::Color::White);
		text_100000.setCharacterSize(20);
		text_100000.setPosition(sf::Vector2f(820.0, 920));
		window.draw(text_100000);

		sf::Text value1_100000;
		value1_100000.setFont(font);
		value1_100000.setString(std::to_string(time_spent_normal[2]));
		value1_100000.setFillColor(sf::Color::Green);
		value1_100000.setCharacterSize(15);
		value1_100000.setPosition(sf::Vector2f(820.0, 870 - time_spent_normal[2]));
		window.draw(value1_100000);

		sf::Text value2_100000;
		value2_100000.setFont(font);
		value2_100000.setString(std::to_string(time_spent_bigrange[2]));
		value2_100000.setFillColor(sf::Color::Red);
		value2_100000.setCharacterSize(15);
		value2_100000.setPosition(sf::Vector2f(945.0, 870 - time_spent_bigrange[2]));
		window.draw(value2_100000);

		//legend

		sf::Text legend_green;
		legend_green.setFont(font);
		legend_green.setString("Range = Dizi Boyutu");
		legend_green.setFillColor(sf::Color::White);
		legend_green.setCharacterSize(13);
		legend_green.setPosition(sf::Vector2f(180.0, 70.0));
		window.draw(legend_green);

		sf::RectangleShape legend_greenr(sf::Vector2f(20.0, 20.0));
		legend_greenr.setFillColor(sf::Color::Green);
		legend_greenr.setPosition(152.0, 68.0);
		window.draw(legend_greenr);

		sf::Text legend_red;
		legend_red.setFont(font);
		legend_red.setString("Range = Dizi Boyutu * 10");
		legend_red.setFillColor(sf::Color::White);
		legend_red.setCharacterSize(13);
		legend_red.setPosition(sf::Vector2f(180.0, 95.0));
		window.draw(legend_red);

		sf::RectangleShape legend_redr(sf::Vector2f(20.0, 20.0));
		legend_redr.setFillColor(sf::Color::Red);
		legend_redr.setPosition(152.0, 93.0);
		window.draw(legend_redr);
		
		window.display();
	}
	return 0;
}
