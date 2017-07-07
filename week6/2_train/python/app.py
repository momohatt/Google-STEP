# -*- coding: utf-8 -*-

import urllib2
import json
import webapp2
import cgi

data = []
adjList = [[]]

class MainPage(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/html'
        self.response.write('<title> Train Transit in Tokyo</title>')
        self.response.write('<body> <form action = "/search">')
        self.response.write('<h1> Train Transit </h1>')
        self.response.write('<h3> Depart from: <select name = "from">')
        for dictionary in data:
            for station in dictionary['Stations']:
                self.response.write('<option>%s - %s </option>' %(dictionary['Name'], station))
        self.response.write('</select> </h3>')

        self.response.write('<h3> Arrive at: <select name = "to">')
        for dictionary in data:
            for station in dictionary['Stations']:
                self.response.write('<option>%s - %s </option>' %(dictionary['Name'], station))

        self.response.write('</select> </h3>')
        self.response.write('<input type = "submit" value = "search"> </form> </body>')


class SearchTransit(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/html'
        self.response.write('<title>Search Result</title>')
        self.response.write('<body> <h1> Search Result </h1>')
        start = self.request.get("from")
        end = self.response.get("to")
        
    def makeAdjList(self):
        global data
        global adjList
        for dictionary in data:
            for station in dictionary['Stations']:
                adjList[station].append(dictionary['Stations'][station - 1])
                adjList[station].append(dictionary['Stations'][station + 1])
        return

    def bfs(self, start, end):
        global data
        global adjList
        queue = []
        dist = [10000] * 1000
        while True:
            for i in range
            


def handleData():
    response = urllib2.urlopen('http://lotr.fantasy-transit.appspot.com/net?format=json').read().decode('utf-8')
    global data 
    data = json.loads(response)
    #print(data)
    #for dictionary in data:
    #    for station in dictionary['Stations']:
    #        print(dictionary['Name'], station)
    return

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/search', SearchTransit)
], debug = True)

def main():
    from paste import httpserver
    handleData()
    httpserver.serve(app, host='127.0.0.1', port='8080')
    return

if __name__ == '__main__':
    main()
    




