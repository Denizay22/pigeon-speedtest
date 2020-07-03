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
	//dizinin elemanlarının tutulacağı pigeon hollerin açılması
	int* phole = (int*)malloc(range * sizeof(int));
	memset(phole, 0, range * sizeof(int));
	//elemanların pigeon hollere yerleştirilmesi
	for (i = 0; i < n; i++)
		phole[arr[i] - min]++;
	//pigeon hollerdeki elemanların tekrardan diziye geri konulması
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

	/* sırayla 1.000, 10.000 ve 100.000 elemanlı 2'şer dosya, toplam 6 dosya okunup diziye aktarılıyor.
	pigeonhole sorting, dizinin eleman sayısı ve range'i birbirine ne kadar yakınsa teoride o kadar hızlı çalıştığı
	için, range'i eleman sayısıyla eşit olan ve range'i eleman sayısının 10 katı fazla olan 2 farklı dizi sıralanıyor.
	bu işlemlerin süresi std::chrono::high_resolution_clock ile nanometre hassaslığında ölçülüyor.*/



	long int* arr_1000 = (long int*)malloc(1000 * sizeof(long int));
	//dosyanın okunup diziye aktarılması
	FILE* arr1000 = fopen("1000.txt", "r");
	for (i = 0; i < 1000; i++) {
		fscanf(arr1000, "%d", &arr_1000[i]);
	}
	//pigeonholeSort fonksiyonunun çağırılıp dizinin sıralanması, aynı zamanda sıralanırken geçen süre de ölçülüyor
	auto start = std::chrono::high_resolution_clock::now();
	pigeonholeSort(arr_1000, 1000);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	time_spent_normal[0] = duration;
	fclose(arr1000);
	//yukarıdaki aynı işlem, range'i dizinin eleman sayısından 10 kat fazla olan başka bir dizi için de yapılıyor
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

	//aynı işlem 10.000 eleman sayılı dizi için yapılıyor

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

	//aynı işlem 100.000 eleman sayılı dizi için yapılıyor

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

	/*süre ölçümleri arasındaki fark çok fazla olduğu için(binlerce hatta onbinlerce kat fark var),
	bu sürelerin normalize edilmesi gerekiyor. bu yüzden minimum ve maksimum bulunup süreler
	normalize ediliyor(6 ve 850 arasında)*/

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
		time_spent_normal[i] = NORMALIZE; //NORMALIZE VE NORMALIZEB kodun en üstünde tanımlanmış birer makro
		time_spent_bigrange[i] = NORMALIZEB;
	}

	printf("          RANGE = ELEMAN SAYISI                   RANGE = ELEMAN SAYISI * 10\n\n");
	for (i = 0; i < 3; i++) {
		printf("           %f birim sure                        %f birim sure\n\n", time_spent_normal[i], time_spent_bigrange[i]);
	}
	//Burdan sonrası verilerin ekrana yazdırılması. Ekrana yazdırırken SFML kullandım (VS19 üzerinde) eğer SFML kullanmak istemiyorsanız
	//kodun burdan sonraki kısmını silebilirsiniz

	//ekrana çıkacak yazıların fontu
	sf::Font font;
	if (!font.loadFromFile("font.otf")) {
		printf("\n Font yuklenirken hata olustu\n");
	}

	//ekranın boyutunun belirlenmesi
	float width = (float)sf::VideoMode::getDesktopMode().width * 100.0 / 192.0;
	float height = (float)sf::VideoMode::getDesktopMode().height * 100.0 / 108.0;
	sf::RenderWindow window(sf::VideoMode(width, height), "Pigeonhole Sort Verileri");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		
		//X ve Y koordinatlarının ekrana çizilmesi
		
		sf::RectangleShape y_axis(sf::Vector2f(1.0, height * 0.86));
		y_axis.setPosition(width * 0.03, height * 0.04);
		y_axis.setFillColor(sf::Color::White);
		window.draw(y_axis);
		sf::RectangleShape x_axis(sf::Vector2f(width * 0.92, 1.0));
		x_axis.setPosition(width * 0.03, height * 0.9);
		x_axis.setFillColor(sf::Color::White);
		window.draw(x_axis);

		//range = eleman sayısı olan dizilerin ekrana çizilmesi
		
		sf::RectangleShape t0(sf::Vector2f(width * 0.078125, time_spent_normal[0]));
		t0.setPosition(width * 0.07, height * 0.9 - time_spent_normal[0]);
		t0.setFillColor(sf::Color::Green);
		window.draw(t0);

		sf::RectangleShape t1(sf::Vector2f(width * 0.078125, time_spent_normal[1]));
		t1.setPosition(width * 0.4, height * 0.9 - time_spent_normal[1]);
		t1.setFillColor(sf::Color::Green);
		window.draw(t1);
		
		sf::RectangleShape t2(sf::Vector2f(width * 0.078125, time_spent_normal[2]));
		t2.setPosition(width * 0.73, height * 0.9 - time_spent_normal[2]);
		t2.setFillColor(sf::Color::Green);
		window.draw(t2);
		
		//range = eleman sayısı * 10 olan dizilerin ekrana çizilmesi

		sf::RectangleShape t0_b(sf::Vector2f(width * 0.078125, time_spent_bigrange[0]));
		t0_b.setPosition(width * 0.2, height * 0.9 - time_spent_bigrange[0]);
		t0_b.setFillColor(sf::Color::Red);
		window.draw(t0_b);

		sf::RectangleShape t1_b(sf::Vector2f(width * 0.078125, time_spent_bigrange[1]));
		t1_b.setPosition(width * 0.53, height * 0.9 - time_spent_bigrange[1]);
		t1_b.setFillColor(sf::Color::Red);
		window.draw(t1_b);

		sf::RectangleShape t2_b(sf::Vector2f(width * 0.078125, time_spent_bigrange[2]));
		t2_b.setPosition(width * 0.86, height * 0.9 - time_spent_bigrange[2]);
		t2_b.setFillColor(sf::Color::Red);
		window.draw(t2_b);

		//yazıların ekrana çizilmesi

		sf::Text text_1000;
		text_1000.setFont(font);
		text_1000.setString("Dizi Boyutu = 1000");
		text_1000.setFillColor(sf::Color::White);
		text_1000.setCharacterSize(20);
		text_1000.setPosition(sf::Vector2f(width * 0.06, height * 0.92));
		window.draw(text_1000);

		
		sf::Text value1_1000;
		value1_1000.setFont(font);
		value1_1000.setString(std::to_string(time_spent_normal[0]));
		value1_1000.setFillColor(sf::Color::Green);
		value1_1000.setCharacterSize(15);
		value1_1000.setPosition(sf::Vector2f(width * 0.068, height * 0.87 - time_spent_normal[0]));
		window.draw(value1_1000);

		sf::Text value2_1000;
		value2_1000.setFont(font);
		value2_1000.setString(std::to_string(time_spent_bigrange[0]));
		value2_1000.setFillColor(sf::Color::Red);
		value2_1000.setCharacterSize(15);
		value2_1000.setPosition(sf::Vector2f(width * 0.198, height * 0.87 - time_spent_bigrange[0]));
		window.draw(value2_1000);

		sf::Text text_10000;
		text_10000.setFont(font);
		text_10000.setString("Dizi Boyutu = 10000");
		text_10000.setFillColor(sf::Color::White);
		text_10000.setCharacterSize(20);
		text_10000.setPosition(sf::Vector2f(width * 0.39, height * 0.92));
		window.draw(text_10000);

		sf::Text value1_10000;
		value1_10000.setFont(font);
		value1_10000.setString(std::to_string(time_spent_normal[1]));
		value1_10000.setFillColor(sf::Color::Green);
		value1_10000.setCharacterSize(15);
		value1_10000.setPosition(sf::Vector2f(width * 0.395, height * 0.87 - time_spent_normal[1]));
		window.draw(value1_10000);

		sf::Text value2_10000;
		value2_10000.setFont(font);
		value2_10000.setString(std::to_string(time_spent_bigrange[1]));
		value2_10000.setFillColor(sf::Color::Red);
		value2_10000.setCharacterSize(15);
		value2_10000.setPosition(sf::Vector2f(width * 0.525, height * 0.87 - time_spent_bigrange[1]));
		window.draw(value2_10000);



		sf::Text text_100000;
		text_100000.setFont(font);
		text_100000.setString("Dizi Boyutu = 100000");
		text_100000.setFillColor(sf::Color::White);
		text_100000.setCharacterSize(20);
		text_100000.setPosition(sf::Vector2f(width * 0.71, height * 0.92));
		window.draw(text_100000);

		sf::Text value1_100000;
		value1_100000.setFont(font);
		value1_100000.setString(std::to_string(time_spent_normal[2]));
		value1_100000.setFillColor(sf::Color::Green);
		value1_100000.setCharacterSize(15);
		value1_100000.setPosition(sf::Vector2f(width * 0.72, height * 0.87 - time_spent_normal[2]));
		window.draw(value1_100000);

		sf::Text value2_100000;
		value2_100000.setFont(font);
		value2_100000.setString(std::to_string(time_spent_bigrange[2]));
		value2_100000.setFillColor(sf::Color::Red);
		value2_100000.setCharacterSize(15);
		value2_100000.setPosition(sf::Vector2f(width * 0.847, height * 0.87 - time_spent_bigrange[2]));
		window.draw(value2_100000);

		//legend

		sf::Text legend_green;
		legend_green.setFont(font);
		legend_green.setString("Range = Dizi Boyutu");
		legend_green.setFillColor(sf::Color::White);
		legend_green.setCharacterSize(13);
		legend_green.setPosition(sf::Vector2f(width * 0.09, height * 0.07));
		window.draw(legend_green);

		sf::RectangleShape legend_greenr(sf::Vector2f(width * 0.02, height * 0.020));
		legend_greenr.setFillColor(sf::Color::Green);
		legend_greenr.setPosition(width * 0.062, height * 0.068);
		window.draw(legend_greenr);

		sf::Text legend_red;
		legend_red.setFont(font);
		legend_red.setString("Range = Dizi Boyutu * 10");
		legend_red.setFillColor(sf::Color::White);
		legend_red.setCharacterSize(13);
		legend_red.setPosition(sf::Vector2f(width * 0.09, height * 0.095));
		window.draw(legend_red);

		sf::RectangleShape legend_redr(sf::Vector2f(width * 0.02, height * 0.020));
		legend_redr.setFillColor(sf::Color::Red);
		legend_redr.setPosition(width * 0.062, height * 0.093);
		window.draw(legend_redr);
		
		window.display();
	}
	return 0;
}
