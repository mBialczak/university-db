#include "DBdataGenerator.hpp"

#include <string>

namespace university::data_generator {

const std::vector<std::string> DBdataGenerator::femaleFirstNames = {
    "Aneta",
    "Anita"
    "Anna",
    "Agata",
    "Alicja",
    "Barbara",
    "Beata",
    "Berta",
    "Bianka",
    "Brygida",
    "Cecylia",
    "Celina",
    "Dagmara",
    "Dalia",
    "Danuta",
    "Diana",
    "Dorota",
    "Edyta",
    "Elena",
    "Eliza",
    "Emilia",
    "Ewa",
    "Ewelina",
    "Felicja",
    "Fiona",
    "Gertruda",
    "Gracja",
    "Halina",
    "Hiacynta",
    "Honorata",
    "Iga",
    "Irena",
    "Jadwiga",
    "Jagoda",
    "Joanna",
    "Justyna",
    "Kaja",
    "Kalina",
    "Karolina",
    "Kinga",
    "Kleopata",
    "Leokadia",
    "Lidia",
    "Lukrecja",
    "Magdalena",
    "Malwina",
    "Marta",
    "Marzena",
    "Milena",
    "Monika",
    "Nadia",
    "Natalia",
    "Nina",
    "Ofelia",
    "Oliwia",
    "Otylia",
    "Pamela",
    "Paulina",
    "Pola",
    "Ramona",
    "Renata",
    "Regina",
    "Roksana",
    "Sabina",
    "Sandra",
    "Sara",
    "Sonia",
    "Sylwia",
    "Tamara",
    "Teresa",
    "Tina",
    "Ula",
    "Urszula",
    "Wanessa",
    "Weronika",
    "Wiktoria",
    "Wioletta",
    "Zofia",
    "Zuzanna"
};

const std::vector< std::string> DBdataGenerator::maleFirstNames {
    "Abelard",
    "Adam",
    "Adrian",
    "Alan",
    "Albin",
    "Aleksander",
    "Antoni",
    "Baltazar",
    "Bartosz",
    "Bazyli",
    "Brunon",
    "Ceazary",
    "Chrystian",
    "Cyprian",
    "Damazy",
    "Daniel",
    "Dariusz",
    "Dawid",
    "Dominik",
    "Edgar",
    "Edward",
    "Emil",
    "Fabian",
    "Feliks",
    "Filip",
    "Fryderyk",
    "Gabriel",
    "Gerard",
    "Gerwazy",
    "Grzegorz",
    "Hektor",
    "Henryk",
    "Horacy",
    "Hugo",
    "Ignacy",
    "Igor",
    "Ireneusz",
    "Jacek",
    "Janusz",
    "Jerzy",
    "Julian",
    "Juliusz",
    "Kacper",
    "Kamil",
    "Karol",
    "Konrad",
    "Krystian",
    "Lech",
    "Leon",
    "Leszek",
    "Lucjan",
    "Ludomir",
    "Ludwik",
    "Maciej",
    "Marcel",
    "Marek",
    "Maria",
    "Marian",
    "Napoleon",
    "Norbert",
    "Olek",
    "Oskar",
    "Patryk",
    "Robert",
    "Roman",
    "Samir",
    "Szymon",
    "Tadeusz",
    "Tomasz",
    "Teofil",
    "Walenty",
    "Wiktor",
    "Witold",
    "Wojciech",
    "Zbigniew",
    "Zenon",
    "Zygmunt"
};

const std::vector<std::string> DBdataGenerator::lastNames {
    "Abbot",
    "Ackerman",
    "Adamczyk",
    "Adamowicz",
    "Adwell",
    "Aleksandrowicz",
    "Alford",
    "Andrzejak",
    "Araszkiewicz",
    "Bachleda",
    "Bachus",
    "Bacon",
    "Baham",
    "Ballard",
    "Barlow",
    "Baron",
    "Berent",
    "Baskerville",
    "Baj",
    "Berman",
    "Bies",
    "Boruc",
    "Caldwell",
    "Callaham",
    "Cambridge",
    "Caywood",
    "Chlebek",
    "Chmiel",
    "Czachor",
    "Danbury",
    "Dancewicz",
    "Danford",
    "Daniels",
    "Darcey",
    "Darlington",
    "Delaney",
    "Drewnowicz",
    "Duda",
    "Dziadosz",
    "Dziuba",
    "Eagleton",
    "Egerton",
    "Emerson",
    "Fairweather",
    "Fetherston",
    "Fikus",
    "Fishburne",
    "Flemming",
    "Fogiel",
    "Gale",
    "Galley",
    "Gancarczyk",
    "Gawrysiak",
    "Germann",
    "Gifford",
    "Glinka",
    "Godbold",
    "Gondz",
    "Grassman",
    "Gryga",
    "Gut",
    "Hackman",
    "Hadfield",
    "Hardman",
    "Harwood",
    "Hejmo",
    "Hermanowicz",
    "Higginson",
    "Iddings",
    "Ignatowicz",
    "Ivory",
    "Jachimowicz",
    "Jackman",
    "Jacobson",
    "Jakimowicz",
    "Janczak",
    "Jenkins",
    "Josselyn",
    "Jurczyk",
    "Kaczmarek",
    "Kaczor",
    "Kandefer",
    "Kasprowicz",
    "Kasprzyk",
    "Katlewicz",
    "Keithley",
    "Kempton",
    "Kenward",
    "Kirchner",
    "Klimczuk",
    "Klimek",
    "Kmiecik",
    "Kocot",
    "Kopiczko",
    "Korona",
    "Kosowski",
    "Kotecki",
    "Kotowski",
    "Kowalczyk",
    "Krawczyk",
    "Kubicz",
    "Kucharczyk",
    "Kukiz",
    "Kupczak",
    "Kwiek",
    "Lacey",
    "Ladley",
    "Lamberton",
    "Lanford",
    "Lasocki",
    "Ledington",
    "Leja",
    "Lewek",
    "Mackiewicz",
    "Maddex",
    "Malak",
    "Maltman",
    "Maniura",
    "Mansel",
    "Marchman",
    "Martens",
    "Mazur",
    "Mazurek",
    "Miazga",
    "Michnik",
    "Narkiewicz",
    "Nazworth",
    "Needham",
    "Nettleton",
    "Nicholson",
    "Nowak",
    "Nutter",
    "Ochab",
    "Oldfield",
    "Olechnowicz",
    "Olejniczak",
    "Olmsted",
    "Onufrowicz",
    "Orsborn",
    "Oxford",
    "Padmore",
    "Paliwoda",
    "Palmerton",
    "Pankiewicz",
    "Partyka",
    "Paszek",
    "Patman",
    "Pawlak",
    "Pazura",
    "Pearson",
    "Pelc",
    "Perham",
    "Peterson",
    "Piecha",
    "Piechota",
    "Pietrasiak",
    "Pietrzak",
    "Piszcz",
    "Piwowarczyk",
    "Pluta",
    "Popek",
    "Popwell",
    "Presley",
    "Quincey",
    "Rachford",
    "Rainbow",
    "Randall",
    "Rambo",
    "Reszke",
    "Romanowicz",
    "Roseman",
    "Rubinowicz",
    "Rutowicz",
    "Ryndak",
    "Rys",
    "Rzeszutko",
    "Sainsbury",
    "Samek",
    "Samford",
    "Samsonowicz",
    "Sandler",
    "Sayer",
    "Schutt"
    "Sembratowicz",
    "Semik",
    "Seward",
    "Siczek",
    "Sienkiewicz",
    "Sieradzan",
    "Sikora",
    "Skoczylas",
    "Skrok",
    "Smolar",
    "Smolik",
    "Snopkiewicz",
    "Sochan",
    "Sojka",
    "Stachyra",
    "Stasiak",
    "Stasiuk",
    "Stenka",
    "Stoch",
    "Strzoda",
    "Sulej",
    "Syrewicz",
    "Sytek",
    "Szafarz",
    "Szajda",
    "Szczepanik",
    "Szczurek",
    "Sczytko",
    "Szebesta",
    "Szemiot",
    "Szmejter",
    "Szojda",
    "Szostak",
    "Szymanek",
    "Szymczyk",
    "Taplin",
    "Tenneson",
    "Teodorowicz",
    "Tochowicz",
    "Trynkiewicz",
    "Tuchlin",
    "Tyrcha",
    "Turowicz",
    "Tyszka",
    "Unrug",
    "Vanstone",
    "Vassel",
    "Vetulani",
    "Wachowicz",
    "Wallman",
    "Washington",
    "Wasiak",
    "Wasil",
    "Wilk",
    "Witczak",
    "Wojcik",
    "Wojnar",
    "Wyrwa",
    "Zacharewicz",
    "Zane",
    "Zaremba",
    "Zaucha",
    "Zawada",
    "Zawisza",
    "Zdanowicz",
    "Zelek",
    "Zielonko",
    "Zych"
};

}   // namespace university::data_generator