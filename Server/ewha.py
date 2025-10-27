import re

stu={19700**: ['서**', 'Michael Jackson', 'Hydrogen', 'Seoul', 1847293650, 143],
 21700**: ['김**', 'Freddie Mercury', 'Helium', 'Tokyo', 9283746510, 178],
 21700**: ['이**', 'Elvis Presley', 'Lithium', 'Beijing', 3759482016, 125],
 22031**: ['이**', 'John Lennon', 'Beryllium', 'Shanghai', 6024837195, 191],
 22700**: ['고**', 'Paul McCartney', 'Boron', 'Bangkok', 8371920456, 104],
 22700**: ['이**', 'David Bowie', 'Carbon', 'Singapore', 2946738105, 167],
 22700**: ['김**', 'Prince', 'Nitrogen', 'Mumbai', 5108374629, 132],
 22700**: ['심**', 'Beyonce', 'Oxygen', 'Dubai', 7392846015, 156],
 22701**: ['안**', 'Adele', 'Fluorine', 'Istanbul', 4628391057, 189],
 22980**: ['김**', 'Taylor Swift', 'Neon', 'Moscow', 8015729364, 113],
 22770**: ['김**', 'Lady Gaga', 'Sodium', 'London', 3847261950, 147],
 23700**: ['이**', 'Madonna', 'Magnesium', 'Paris', 9562018374, 172],
 23700**: ['정**', 'Whitney Houston', 'Aluminum', 'Berlin', 1739485026, 108],
 23910**: ['이**', 'Mariah Carey', 'Silicon', 'Rome', 6285034719, 195],
 24800**: ['조**', 'Bruno Mars', 'Phosphorus', 'Madrid', 4920573816, 121],
 24660**: ['이**', 'Ed Sheeran', 'Sulfur', 'Amsterdam', 8346192750, 164],
 25510**: ['정**', 'Ariana Grande', 'Chlorine', 'Vienna', 2051847396, 138],
 25170**: ['박**', 'Billie Eilish', 'Argon', 'Prague', 7428360915, 151],
 25660**: ['서**', 'Drake', 'Potassium', 'New York', 5693817204, 183],
 25670**: ['김**', 'The Weeknd', 'Calcium', 'Los Angeles', 9184027356, 117],
 25670**: ['박**', 'Frank Sinatra', 'Scandium', 'Toronto', 3627491850, 159],
 25670**: ['신**', 'Stevie Wonder', 'Titanium', 'Mexico City', 6947283015, 126],
 25670**: ['양**', 'Aretha Franklin', 'Vanadium', 'São Paulo', 1582739460, 194],
 25670**: ['이**', 'Ray Charles', 'Chromium', 'Buenos Aires', 8263945017, 103],
 25670**: ['임**', 'Shakira', 'Manganese', 'Sydney', 4739201856, 175],
 25932**: ['임**', 'Andrea Bocelli', 'Iron', 'Cairo', 7015382649, 141]}

def lookup(args):
    no=args.get("hakbun","")
    name=args.get("name","")
    print(no, name)

    if not re.match("\\d{7}", no):
        return "no good hakbun",200,{}
    no=int(no)

    if no in stu:
        print(f'found {no} {name} {stu[no]}')
        if stu[no][0]==name:
            return stu[no][1],200,{'element':stu[no][2]}

    return "no good name",200,{}

if __name__ == "__main__":
    print(lookup({"hakbun":"23700**", "name":"이**"}))
