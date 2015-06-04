#ifndef EFFECTGUI_H
#define EFFECTGUI_H
#include "drawables.h"
#include "effects.h"

	///Struktura zawierająca obiekt rysowalny obsługujący paramert (suwak, suwak stopniowy lub bus) i teksturę z nazwą parametru
	struct ParamDrawable
	{
		Drawable* drawable; ///obiekt rysowalny
		SDL_Texture* nameTex=NULL; ///tekstura z nazwą
		bool vertical; ///czy tekst ma być pionowy
		ParamDrawable(Drawable* d, const char* text, bool v=false): drawable(d), vertical(v)
		{
			if(vertical) nameTex=generateVerticalText(text);
			else nameTex=generateText(text);
		}
		
		///rysuje obiekt rysowalny (tylko)
		void draw() 
		{
			drawable->draw();
		}
		
		///rysuje tekst pod/obok obiektu rysowalnego
		void drawText()
		{
			if(!vertical)
			{
				int w, h;
				SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
		
				SDL_Rect nameRect;
				nameRect.x=drawable->getPosX() + drawable->getWidth()/2 - w/2;
				nameRect.y=drawable->getPosY() + drawable->getHeight(); 
				nameRect.w=w;
				nameRect.h=h;		
				
				SDL_RenderCopy(render, nameTex, NULL, &nameRect);
			}
			else
			{
				int w, h;
				SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
		
				SDL_Rect nameRect;
				nameRect.x=drawable->getPosX() - w -2;
				nameRect.y=drawable->getPosY() + drawable->getHeight() - h; 
				nameRect.w=w;
				nameRect.h=h;
				
				SDL_RenderCopy(render, nameTex, NULL, &nameRect);
			}
		}
		
		///zwalnia pamięć tekstury
		void free() {delete drawable; SDL_DestroyTexture(nameTex);}
	};
	
	///Enum na wszystkie obiekty rysowalne 
	enum VisulalisationType{
			VT_NONE,
      VT_INBUS,
      VT_OUTBUS,
			VT_FREQ_INBUS,
			VT_FREQ_OUTBUS,
			VT_AMP_INBUS,
			VT_AMP_OUTBUS,
			VT_FEEDBACK_INBUS,
			VT_FEEDBACK_OUTBUS,
      VT_SLIDER,
			VT_GRADUALSLIDER,
			VT_ENTRYBOX,
			VT_SWITCHBUTTON,
			VT_TEXT
    };
	
	///Struktura na tablicę floutów - używana przy suwaku stopniowym (GradualSlider)
	struct FloatArray
	{
		int count; ///ilość elementów
		float* array; ///tablica
		FloatArray(int count, ...)
		{
			this->count=count;
			array=new float[count];
			va_list vl;
			va_start(vl,count);
			for(int i=0;i<count;++i)
			{
				array[i]=va_arg(vl,double);
			}
			va_end(vl);
		}
		~FloatArray()
		{
			delete [] array;
		}
	};
	
	///Struktura z opisem wizualizacji danego efektu
	///W niej zapisana jest informacja o  tym czy argument ma być np. suwakiem czy busem
    class ArgVis
    {
		private:
			size_t getDataSize() const{
				switch(visType){
					case VT_SLIDER: return sizeof(float)*2 + sizeof(int)*2;
					case VT_SWITCHBUTTON: return sizeof(float)*2 + sizeof(int)*2 + sizeof(bool);
					case VT_GRADUALSLIDER: return count*sizeof(float);
					case VT_TEXT: return -1; // N/A
					default: return 0; // N/A
				}
			}
		public:
        VisulalisationType visType; ///typ obiektu
        void* data=NULL; ///dodatkowo zhardkodowane dane
				int count = 0; // stores element count for array data types
        
		///Konstruktor dla visType=VT_SLIDER parametry to początek i koniec przedziału, oraz wysokość i szerokość suwaka
        ArgVis(VisulalisationType, float min, float max, int width=0, int height=0)
        {
				visType=VT_SLIDER;
				data=malloc(getDataSize());
				((float*)data)[0]=min;
				((float*)data)[1]=max;
				((int*)(((float*)data)+2))[0]=width;
				((int*)(((float*)data)+2))[1]=height;
        }
		
		///Konstruktor dla visType=VT_SWITCHBUTTON parametry to 2 wartości przełącznika, wymbole odpowiadające wartością oraz czy przełącznik ma być trigerem
		ArgVis(VisulalisationType, float value1, float value2, int symbol1, int symbol2, bool triger)
        {
				visType=VT_SWITCHBUTTON;
				data=malloc(getDataSize());
				((float*)data)[0]=value1;
				((float*)data)[1]=value2;
				((int*)(((float*)data)+2))[0]=symbol1;
				((int*)(((float*)data)+2))[1]=symbol2;
				*((bool*)((int*)(((float*)data)+2)+2))=triger;
        }
		
		///Konstruktor dla visType=VT_GRADUALSLIDER generuje tablicę z liczb całkowitych o podanym przedziale
		ArgVis(VisulalisationType, int min, int max)
        {
			count=max-min+1;
			
			visType=VT_GRADUALSLIDER;
      data=malloc(getDataSize());
			
			float* tab=(float*)((int*)data);

			for(int i=min;i<=max;++i)
			{
				tab[i-min]=float(i);
			}
			
		}
		
		///Konstruktor dla visType=VT_GRADUALSLIDER, tablica podawana jest w parametrze
		ArgVis(VisulalisationType, FloatArray floatArray)
    {
      visType=VT_GRADUALSLIDER;
			count = floatArray.count;
      data=malloc(getDataSize());
	
			float* tab=(float*)((int*)data);
			
			for(int i=0;i<floatArray.count;++i)
			{
				tab[i]=floatArray.array[i];
			}
    }
		
		///Konstruktor dla visType=VT_TEXT, jedynym parametrem jest tekst do wyświetlenia
		ArgVis(VisulalisationType, std::string str)
        {
            visType=VT_TEXT;
            data=new std::string(str);
        }
		
		///Konstruktor dla visType które nie mają dodatkowych parametrów
        ArgVis(VisulalisationType type)
        {
            visType=type;
        }

        ~ArgVis()
        {
          if(visType==VT_SLIDER)
						free(data);
					else if(visType==VT_GRADUALSLIDER)
						free(data);
					else if(visType==VT_TEXT)
						delete (std::string*)data;
        }
        
			ArgVis(const ArgVis& other){
				visType = other.visType;
				count = other.count;
				if(visType == VT_TEXT) data = new std::string(*((std::string*)data));
				else{
					data = malloc(other.getDataSize());
					memcpy(data, other.data, other.getDataSize());
				}
			}

    };
	
	typedef std::pair<int, int> int_pair;
	
	class EffectGUI : public Effect
	{	
		friend class Controller;
	
		Button* pauseButton; ///przycisk od pauzowania efektu
		
		int handlePosX, handlePosY; ///miejsce ciągnięcia okna myszą
		
		bool focus=false; ///czy okno jest ciągnięte
		
		SDL_Texture* nameTex; ///tekstura z tytułem okna
		
		protected:
		
		std::vector <ParamDrawable> drawables; ///obiekty rysowalne parametrów
		
		int posX, posY; ///pozycja okna (lewy górny róg)
		
		int width, height; ///szerokość i wysokość okna
		
		public:
		
		static const int slider_width=24; ///domyślna szerokość suwaka
		static const int slider_height=160; ///domyślna wysokość suwaka
		
		static const int entrybox_width=35; ///domyślna szerokość pola do wpisywania
		
		virtual std::vector<int_pair>& getVisualPositions()=0; ///pozycje obiektów rysowalnych (do implementacji przez konkretne efekty lub AutoEfectGUI)
		
		virtual std::vector<ArgVis>& getArgumentVisuals()=0; ///opisy wizualizacji argumentów (do implementacji przez konkretne efekty)
		
		EffectGUI(){}
		EffectGUI(std::string name, std::string fullName) : Effect(name, fullName){}
		
		///inicializuje GUI (do wrzucenia w konstruktor efektu)
		void initGUI(int X, int Y, int W=0, int H=0)
		{
			posX=X;
			posY=Y;
			
			width=W;
			height=H;
			
			pauseButton=new Button(X+2, Y+2, 0);
			
			std::vector<EffectArgument>& args=getArgs();
			int argsCount=getArgsCount();
			
			std::vector<ArgVis>& argvis=getArgumentVisuals();
			
			std::vector<int_pair>& argpos=getVisualPositions();
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_INBUS, this, i), args[i].getName()));
					break;
					case VT_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_FEEDBACK_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FEEDBACK_INBUS, this, i), args[i].getName()));
					break;
					case VT_FEEDBACK_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FEEDBACK_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_FREQ_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FREQ_INBUS, this, i), args[i].getName()));
					break;
					case VT_FREQ_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_FREQ_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_AMP_INBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_AMP_INBUS, this, i), args[i].getName()));
					break;
					case VT_AMP_OUTBUS:
					drawables.push_back(ParamDrawable(new Bus(posX+argpos[i].first, posY+argpos[i].second, BT_AMP_OUTBUS, this, i), args[i].getName()));
					break;
					case VT_SLIDER:
					{
						float min=((float*)argvis[i].data)[0];
						float max=((float*)argvis[i].data)[1];
						int width=((int*)(((float*)argvis[i].data)+2))[0];
						int height=((int*)(((float*)argvis[i].data)+2))[1];
						
						drawables.push_back(ParamDrawable(new Slider(posX+argpos[i].first, posY+argpos[i].second, (width<=0)?slider_width:width, (height<=0)?slider_height:height, min, max, args[i].getFloatValue(), this, i), args[i].getName(), true));
					}
					break;
					case VT_GRADUALSLIDER:
					{
						int count=*(int*)argvis[i].data;
			
						float* tab=(float*)(((int*)argvis[i].data)+1);	
						drawables.push_back(ParamDrawable(new GradualSlider(posX+argpos[i].first, posY+argpos[i].second, slider_width, slider_height, count, tab, args[i].getFloatValue(), this, i), args[i].getName(), true));
					}
					break;
					case VT_ENTRYBOX:
					drawables.push_back(ParamDrawable(new EntryBox(posX+argpos[i].first, posY+argpos[i].second, entrybox_width, args[i].getFloatValue(), this, i), args[i].getName()));
					break;
					case VT_SWITCHBUTTON:
					{
						float value1=((float*)argvis[i].data)[0];
						float value2=((float*)argvis[i].data)[1];
						int symbol1=((int*)(((float*)argvis[i].data)+2))[0];
						int symbol2=((int*)(((float*)argvis[i].data)+2))[1];
						bool triger=*((bool*)((int*)(((float*)argvis[i].data)+2)+2));
						
						drawables.push_back(ParamDrawable(new SwitchButton(posX+argpos[i].first, posY+argpos[i].second, value1, value2, symbol1, symbol2, triger, this, i), args[i].getName(), false));
					}
					break;
					case VT_TEXT:
						drawables.push_back(ParamDrawable(new Point(posX+argpos[i].first, posY+argpos[i].second), ((std::string*)argvis[i].data)->c_str()));
					break;
					default:
					break;
				}
			}
			
			nameTex=generateText(getFullName().c_str());
		}
		
		///deinicializuje GUI (do wrzucenia w destruktor efektu)
		void quitGUI()
		{
			for(auto &drawable : drawables)
				drawable.free();
				
			std::vector<EffectArgument>& args=getArgs();
			int argsCount=getArgsCount();
			std::vector<ArgVis>& argvis=getArgumentVisuals();
		
			for(int i=0;i<argsCount;++i)
			{
				if(argvis[i].visType==VT_OUTBUS || argvis[i].visType==VT_INBUS)
				{
					OSCConn::deleteBus(args[i].getIntValue());
				}
			}
		}
		
		///aktualizuje pozycje obiektów rysowalnych z tablicy zwracanej przez getVisualPositions()
		void updateDrawablePositions()
		{
			int argsCount=getArgsCount();
			
			std::vector<int_pair>& argpos=getVisualPositions();
			
			for(int i=0;i<argsCount;++i)
			{
				drawables[i].drawable->setPos(posX+argpos[i].first, posY+argpos[i].second);
			}
		}
		
		///ustawia pozycję okna (lewy górny róg)
		void setPos(int X, int Y)
		{
			pauseButton->move(X-posX, Y-posY);
			
			for(auto &d : drawables)
				d.drawable->move(X-posX, Y-posY);
				
			posX=X; posY=Y;
		}
		
		//rysuje okno efektu
		void draw()
		{		
			drawWindow(posX, posY, width, height);
			
			int w, h;
			SDL_QueryTexture(nameTex, NULL, NULL, &w, &h);
			
			SDL_Rect nameRect;
			nameRect.y=posY+2;
			nameRect.x=posX+width/2-w/2;
			nameRect.w=w;
			nameRect.h=h;
			
			SDL_RenderCopy(render, nameTex, NULL, &nameRect);
			
			pauseButton->setSymbol(int(isPaused()));
			pauseButton->draw();
			
			for(int i=drawables.size()-1;i>=0;--i)
			{
				drawables[i].drawText();
			}
			
			for(int i=drawables.size()-1;i>=0;--i)
			{
				drawables[i].draw();
			}
		}
		
		bool receiveClick(int X, int Y, MouseEvent me)
		{
			if(pauseButton->receiveClick(X, Y, me)) 
			{
				paused=!paused;
				if(paused)
					pauseInstance();
				else
					unpauseInstance();
			}
			
			if(me==ME_PRESS)
			{
				if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+Button::size)
				{
					handlePosX=X-posX;
					handlePosY=Y-posY;
					focus=true;
					return true;
				}
				else
				focus=false;
			}
			else if(me==ME_REPEAT && focus)
			{
				setPos(X-handlePosX, Y-handlePosY);
				return true;
			}
			else if(me==ME_RELEASE && focus)
			{
				focus=false;
				return true;
			}
			
			for(auto &d : drawables)
				if(d.drawable->receiveClick(X, Y, me)) return true;
			
			return false;
		}
		
		bool receiveSecondClick(int X, int Y, MouseEvent me)
		{
			for(auto &d : drawables)
				if(d.drawable->receiveSecondClick(X, Y, me)) return true;
				
			if(me==ME_PRESS)
			{
				if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height)
				{
					handlePosX=X-posX;
					handlePosY=Y-posY;
					focus=true;
					return true;
				}
				else
				focus=false;
				return false;
			}
			else if(me==ME_REPEAT && focus)
			{
				setPos(X-handlePosX, Y-handlePosY);
				return true;
			}
			else if(me==ME_RELEASE)
			{
				focus=false;
				return true;
			}
			return false;
		}
		
		bool receiveThridClick(int X, int Y, MouseEvent me)
		{
			if(posX<=X && X<=posX+width && posY<=Y && Y<=posY+height && me==ME_PRESS)
			{
				deleteInstance();
				
				delete this;
				return true;
			}
			else return false;
		}
		
		bool receiveKeyboardEvent(SDL_Scancode scancode)
		{
			for(auto &d : drawables)
				if(d.drawable->receiveKeyboardEvent(scancode)) return true;
			return false;
		}
		
		///zapisuje wszystkie wartości argumentów i ich przedziały do strumienia
		virtual void saveData(FILE* file) 
		{
			int argsCount=getArgsCount();
			std::vector<EffectArgument>& args=getArgs();
			std::vector<ArgVis>& argumentVisuals=getArgumentVisuals();
			
			fprintf(file, "%d %d ", posX, posY);
			
			for(int i=0;i<argsCount;++i)
			{
				if(argumentVisuals[i].visType==VT_SLIDER)
				{
					fprintf(file, "%d %f %f %f ", i, args[i].getFloatValue(), ((Slider*)drawables[i].drawable)->getRangeBegin(), ((Slider*)drawables[i].drawable)->getRangeEnd());
				}
			}
			
		}
		
		///zapisuje wszystkie wartości argumentów i ich przedziały ze strumienia
		virtual void loadData(char* str) 
		{
			std::vector<EffectArgument>& args=getArgs();
			
			std::stringstream ss;
			ss<<str;
			
			int X, Y;
			
			ss>>X>>Y;
			
			setPos(X, Y);
			
			int id;
			float value, rangeBegin, rangeEnd;
			
			printf("dupa\n");
			
			while(ss>>id>>value>>rangeBegin>>rangeEnd)
			{					
				args[id].set(value);
				
				((Slider*)drawables[id].drawable)->setValue(value);
				((Slider*)drawables[id].drawable)->setRangeBegin(rangeBegin);
				((Slider*)drawables[id].drawable)->setRangeEnd(rangeEnd);
			}
		}
		
		virtual ~EffectGUI()
		{
			SDL_DestroyTexture(nameTex);
			delete pauseButton;
		}
		
	};
	
    ///Klasa która w przeciwieństwie do EfectGUI nie wymaga implementacji getVisualPositions() - sama ustawia obiekty rysowalne
	class EffectAutoGUI : public EffectGUI
	{
		std::vector<int_pair> visualPositions; ///współżedne obiektów rysowalnych
		
		public:
		
		// These constants' values are defined in effectgui.cpp
		static const int slider_period; ///odległości pomiędzy suwakami
		static const int top_padding; ///górny margines
		static const int bottom_padding; ///dolny margines
		static const int left_padding; ///lewy margines i odległość od busów wejściowych
		static const int right_padding; ///prawy margines i odległość od busów wyjściowych
		static const int bus_period; ///odległość pionowa między busami
		
		///Zwraca pozycje obiektów rysowalnych
		std::vector<int_pair>& getVisualPositions()
		{
			return visualPositions;
		}
		
		EffectAutoGUI(){}
		EffectAutoGUI(std::string name, std::string fullName) : EffectGUI(name, fullName) {}
		
		///inicializacja GUI
		void initGUI(int X, int Y, int custom_left_padding=left_padding, int custom_right_padding=right_padding)
		{
			
			int width=0, height=0;
		
			posX=X;
			posY=Y;
			
			int argsCount=getArgsCount();
			
			visualPositions.resize(argsCount);
			
			int x=width=custom_left_padding+Bus::size+custom_right_padding;
			
			std::vector<ArgVis>& argvis=getArgumentVisuals();
			
			int bus_y=top_padding;
			int slider_y=0;
			int bus_y2=top_padding;
			
			int extra_period=custom_right_padding;
			
			for(int i=0;i<argsCount;++i)
			{
				switch(argvis[i].visType)
				{
					case VT_INBUS:
					case VT_FREQ_INBUS:
					case VT_AMP_INBUS:
					case VT_FEEDBACK_OUTBUS:
						visualPositions[i]=int_pair(0+custom_left_padding, bus_y);
						bus_y+=bus_period;
					break;
					case VT_OUTBUS:
					case VT_FREQ_OUTBUS:
					case VT_AMP_OUTBUS:
					case VT_FEEDBACK_INBUS:
						visualPositions[i]=int_pair(0, bus_y2);
						bus_y2+=bus_period;
					break;
					case VT_SLIDER:
					case VT_GRADUALSLIDER:
					{
						int width=0, height=0;
						if(argvis[i].visType==VT_SLIDER)
						{
							width=((int*)(((float*)argvis[i].data)+2))[0];
							height=((int*)(((float*)argvis[i].data)+2))[1];
						}
						
						width=(width<=0)?slider_width:width;
						height=(height<=0)?slider_height:height;
					
						slider_y=std::max(slider_y, height);
						visualPositions[i]=int_pair(x, 0+top_padding);
						x+=width+slider_period;
						extra_period=custom_right_padding-slider_period;
					}
					break;
					default:
					break;
				}
			}
			
			height=bottom_padding+std::max(std::max(bus_y, bus_y2), top_padding+slider_y);
			
			x+=extra_period;
			
			width=x;
			
			for(int i=0;i<argsCount;++i)
			{
				if(argvis[i].visType==VT_OUTBUS || argvis[i].visType==VT_FREQ_OUTBUS || argvis[i].visType==VT_AMP_OUTBUS || argvis[i].visType==VT_FEEDBACK_INBUS)
				{
					visualPositions[i].first=x;
				}
			}
			
			width+=Bus::size+custom_right_padding;
			
			
			EffectGUI::initGUI(X, Y, width, height);
		}
		
		virtual ~EffectAutoGUI()
		{
		}
		
	};
	
#endif
