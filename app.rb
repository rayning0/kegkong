require 'rubygems'
require 'bundler'
require './environments'

Dir.glob('./lib/*.rb') do |model|
  require model
end

Bundler.require

module KegKong
  
  class App < Sinatra::Application

    get '/' do
      @keg = Keg.last
      erb :home
    end

    get '/index' do
      @kegs = Keg.all
      erb :index
    end

    get '/subscribe' do 
      "Coming soon!"
    end

    get '/reset' do
      @keg = Keg.last
      erb :reset
    end

    get '/keg/:id' do 
      @keg = Keg.find(params[:id])
      erb :show
    end

    post '/keg/create' do
      @keg = Keg.create(params[:keg])
      erb :temp404
    end

    post '/pendejo' do
      @keg = Keg.last
      measurement = @keg.measurements.build(:pulses => params[:body][:pulses], :change_in_volume => params[:body][:pulses]/21198.296)
      measurement.save
    end
  end
end

