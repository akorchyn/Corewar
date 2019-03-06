/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:22:41 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/04 18:03:10 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.hpp"

constexpr int16_t	WIDTH = 2200;
constexpr int16_t	HEIGHT = 1300;

extern SDL_Color	basicColors[5];

int					initSocket()
{
	int		sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4242);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(sock, 2);
	return sock;
}

void				acceptClient(int32_t sock, int32_t &clientSocket, Corewar **corewar,
							 bool &corewarInitialiazed, Window &window)
{
	uint8_t			initPackage[Corewar::initPackageSize];

	sock = initSocket();
	clientSocket = accept(sock, NULL, NULL);
	recv(clientSocket, initPackage, Corewar::initPackageSize, 0);
	*corewar = new Corewar(&window, initPackage);
	corewarInitialiazed = true;
	std::cout << "Connection is set!" << std::endl;
}

void				drawPreview(Window *window, bool isWaiting)
{
	static Text preview = Text("COREWAR", "fonts/joystix monospace.ttf",
					100, WIDTH / 2 - (100 * 7) / 2,
					HEIGHT / 2 - 100 / 2, 100, 100,
					&basicColors[FIRST], window->renderer);
	static Text pressEnter = Text("Press enter to accept new bunch of fools", "fonts/joystix monospace.ttf",
					15, WIDTH / 2 - (15 * strlen("Press enter to accept new bunch of fools")) / 2,
					HEIGHT / 2 - 15 / 2 + 75, 15, 20,
					&basicColors[SECOND], window->renderer);
	static Text waiting = Text("Waiting...", "fonts/joystix monospace.ttf",
					13, WIDTH / 2 - (10 * strlen("Waiting...")) / 2,
					HEIGHT / 2 - 14 / 2 + 100, 14, 14,
					&basicColors[THIRD], window->renderer);
	static Text authors = Text("Press F to see the creators", "fonts/joystix monospace.ttf",
					16, 20, HEIGHT - 35, 16, 16,
					&basicColors[FOURTH], window->renderer);

	preview.draw();
	pressEnter.draw();
	authors.draw();
	if (isWaiting)
		waiting.draw();
}

void				drawCreators(Window *window)
{
	static SDL_Surface *kpshenycSurf = IMG_Load("creators/kpshenyc.jpg");
	static SDL_Texture *kpshenycText = SDL_CreateTextureFromSurface(window->renderer, kpshenycSurf);
	static SDL_Rect		kpshenycRect = {.h = 300, .w = 250, .x = 0 + 500, .y = 0 + 250};
	static Text			kpshenycTask = Text("kpshenyc", "fonts/joystix monospace.ttf",
											38, 500,
											250 + 300,
											500, 250,
											&basicColors[SECOND], window->renderer);
	kpshenycTask.draw();
	SDL_RenderCopy(window->renderer, kpshenycText, nullptr, &kpshenycRect);

	static SDL_Surface *akorchynSurf = IMG_Load("creators/akorchyn.jpg");
	static SDL_Texture *akorchynText = SDL_CreateTextureFromSurface(window->renderer, akorchynSurf);
	static SDL_Rect		akorchynRect = {.h = 300, .w = 250, .x = WIDTH - 500 - 250, .y = 0 + 250};
	static Text			akorchynTask = Text("akorchyn", "fonts/joystix monospace.ttf",
											38, WIDTH - 500 - 250,
											250 + 300,
											500, 250,
											&basicColors[FIRST], window->renderer);
											SDL_RenderCopy(window->renderer, akorchynText, nullptr, &akorchynRect);
											akorchynTask.draw();
	SDL_RenderCopy(window->renderer, kpshenycText, nullptr, &kpshenycRect);
	akorchynTask.draw();

	static SDL_Surface *dmlitvinSurf = IMG_Load("creators/dmlitvin.jpg");
	static SDL_Texture *dmlitvinText = SDL_CreateTextureFromSurface(window->renderer, dmlitvinSurf);
	static SDL_Rect		dmlitvinRect = {.h = 300, .w = 250, .x = 0 + 500, .y = HEIGHT - 250 - 300};
	static Text			dmlitvinTask = Text("dmlitvin", "fonts/joystix monospace.ttf",
											38, 500,
											HEIGHT - 250,
											500, 250,
											&basicColors[THIRD], window->renderer);
	dmlitvinTask.draw();
	SDL_RenderCopy(window->renderer, dmlitvinText, nullptr, &dmlitvinRect);

	static SDL_Surface *opishcheSurf = IMG_Load("creators/opishche.jpg");
	static SDL_Texture *opishcheText = SDL_CreateTextureFromSurface(window->renderer, opishcheSurf);
	static SDL_Rect		opishcheRect = {.h = 300, .w = 250, .x = WIDTH - 500 - 250, .y = HEIGHT - 250 - 300};
	static Text			opishcheTask = Text("opishche", "fonts/joystix monospace.ttf",
											38, WIDTH - 500 - 250,
											HEIGHT - 250,
											500, 250,
											&basicColors[FOURTH], window->renderer);
	opishcheTask.draw();
	SDL_RenderCopy(window->renderer, opishcheText, nullptr, &opishcheRect);

	static Text			inspiredBy = Text("Inspired by Stura",
							"fonts/joystix monospace.ttf", 30,
								885, 600,
								600, 600,
								&basicColors[THIRD], window->renderer);
	inspiredBy.draw();

	static Text			sponsoredBy = Text("Sponsored by Stura",
											 "fonts/joystix monospace.ttf", 30,
											 875, 650,
											 600, 600,
											 &basicColors[FIRST], window->renderer);
	sponsoredBy.draw();

	static Text			acceleratedBy = Text("Accelerated by Stura",
											  "fonts/joystix monospace.ttf", 30,
											  850, 700,
											  600, 600,
											  &basicColors[SECOND], window->renderer);
	acceleratedBy.draw();

}

void				uninitializeCorewar(Corewar **corewar, Window *window, bool &corewarInitialized, bool &waitingClient,
									int32_t &sock, int32_t &clientSock)
{
	window->preview = true;
	window->isStoped = true;
	corewarInitialized = false;
	waitingClient = false;
	close(sock);
	close(clientSock);
	clientSock = 0;
	sock = 0;
	delete *corewar;
	*corewar = nullptr;
	std::cout << "Disconnecting is done!" << std::endl;
}


int					main(void)
{
	int32_t			clientSock = 0;
	int32_t			sock = 0;
	int8_t			answerToVisualization = 0;

	Window			window("Corewar", WIDTH, HEIGHT);
	Corewar			*corewar;

	uint8_t			fieldPackage[Corewar::fieldPackageSize];
	uint16_t		*carriagesPackage;

	bool			corewarInitialized = false;
	bool			waitingClient = false;

	std::thread th;

	while (!window.isClosed())
	{
		if (!window.preview && !window.creators)
		{
			if (!waitingClient && !corewarInitialized)
			{
				waitingClient = true;
				th = std::thread(acceptClient, sock, std::ref(clientSock),
						&corewar, std::ref(corewarInitialized), std::ref(window));
				th.detach();
			}
			if (corewarInitialized && !window.isStoped)
			{
				send(clientSock, &answerToVisualization, 1, 0);
				if (recv(clientSock, fieldPackage, Corewar::fieldPackageSize, 0) <= 0)
				{
					uninitializeCorewar(&corewar, &window, corewarInitialized, waitingClient, sock, clientSock);
					continue ;
				}
				carriagesPackage = new uint16_t[*((uint32_t *) fieldPackage)];
				send(clientSock, &answerToVisualization, 1, 0);
				if (recv(clientSock, carriagesPackage, *((uint32_t *) fieldPackage) * sizeof(uint16_t), 0) > 0)
					corewar->refreshData(fieldPackage, carriagesPackage, *((uint32_t *)fieldPackage));
				delete[] carriagesPackage;
			}
			if (corewarInitialized)
			{
				corewar->drawInitData(&window);
				corewar->draw(&window);
			}
			else
				drawPreview(&window, waitStatus::WAITING);
		}
		else if (!window.creators && window.preview)
			drawPreview(&window, waitStatus::NOT_WAITING);
		else if (window.creators)
			drawCreators(&window);
		window.poolEvents();
		window.clear();
	}
	if (sock)
		close(sock);
	if (clientSock)
		close(clientSock);
	return (0);
}
